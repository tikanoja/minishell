#include "minishell.h"

int     directory_check(char *str)
{
	struct stat file_info;

	if (stat(str, &file_info) == 0)//protect?
	{
		if (S_ISDIR(file_info.st_mode))
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (1);
		}
		else if(S_ISREG(file_info.st_mode) && access(str, X_OK) != 0)
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("shelly: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int     slash_check(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void    fd_handling2(t_list *current, t_list *head)
{
	int index;

	index = current->index;
	current = head;
	while (current)
	{
		if (current->index != index)
		{
			if (current->input != STDIN_FILENO)
				close(current->input);
			if (current->output != STDOUT_FILENO)
				close(current->output);
		}
		else
		{
			if (current->input != STDIN_FILENO)
			{
				dup2(current->input, STDIN_FILENO);
				close(current->input);
			}
			if (current->output != STDOUT_FILENO)
			{
				dup2(current->output, STDOUT_FILENO);
				close(current->output);
			}
		}
		current = current->next;
	}
}

int    execute_builtin(t_list *current)
{
	pid_t pid;
	int forkflag;
	int status;

	pid = 1; //getpid
	forkflag = 0;
	status = 0;
	if (current->pipe == 1)
	{
		init_child_signals();
		forkflag = 1;
		pid = fork();
		if (pid == -1)
			exitmsg("fork fail\n");
		if (pid == 0)
		{
			fd_handling2(current, get_head_node(current));
			forkflag = 0;
		}
	}
	if (forkflag == 0)
	{
		if (ft_strncmp_casein(current->value, "echo", 5) == 0)
				status = ft_echo(current);
		else if (ft_strncmp_casein(current->value, "pwd", 4) == 0)
				status = ft_pwd();
		else if (ft_strncmp_casein(current->value, "exit", 5) == 0)
				status = ft_exit(current, pid);
		else if (ft_strncmp_casein(current->value, "env", 5) == 0)
				status = ft_env(current, 0);
		else if (ft_strncmp_casein(current->value, "unset", 6) == 0)
				status = ft_unsetenv(current, 0, 0, 0);
		else if (ft_strncmp_casein(current->value, "export", 7) == 0)
				status = ft_export(current);
		else if (ft_strncmp_casein(current->value, "cd", 3) == 0)
				status = ft_cd(current);
		if (pid == 0)
			exit(0);
	}
	return (status);
}

void  execute_system_command(t_list *current, char **envcpy, t_list *head)
{
	pid_t pid;

	pid = fork();
	init_child_signals();
	if (pid == -1)
		exitmsg("fork fail\n");
	else if (pid == 0)
	{
		fd_handling2(current, head);
		if (execve(current->value, current->args, envcpy) == -1)
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(current->value, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(1);
	}
}

void close_all_fds(t_list *current)
{
	while (current)
	{
		if (current->input != STDIN_FILENO)
			close(current->input);
		if (current->output != STDOUT_FILENO)
			close(current->output);
		current = current->next;
	}
}

int    runcmd(t_list *head, char **envcpy)
{
	t_list	*current;
	pid_t	pid;
	int		status;
	
	current = head;
	status = 0;
	while (current)
	{
		if (current->execflag == 1)
		{
			current = current->next;
			continue ;
		}
		if (current->value == NULL)
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(current->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			status = 127;
		}
		else if (slash_check(current->value) == 1 && current->system_command != 1)
		{
			if (directory_check(current->value) != 0)
			{
				current->execflag = 1;
				status = 126;
			}
			else
			{
				current->system_command = 1;
				continue;
			}
		}
		else if (is_it_builtin(current->value) > 0)
			status = execute_builtin(current);
		else if (current->system_command == 1)
			execute_system_command(current, envcpy, head);
		current = current->next;
	}
	current = head;
	close_all_fds(current);
	while ((pid = waitpid(-1, &status, 0)) > 0);
	return (status);
}