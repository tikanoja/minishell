/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:57:35 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_handling2(t_list *current, t_list *head)
{
	int	index;

	index = current->index;
	current = head;
	while (current)
	{
		if (current->index != index)
			fd_handling_close_fds(current);
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

int	builtin_ladder(int status, t_list *current, pid_t pid)
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
	return (status);
}

int	execute_builtin(t_list *current)
{
	pid_t	pid;
	int		forkflag;
	int		status;

	pid = 1;
	forkflag = 0;
	status = 0;
	init_execute_builtin(&pid, &forkflag, &status);
	if (current->pipe == 1)
	{
		init_child_signals();
		forkflag = 1;
		pid = fork();
		if (pid == -1)
			exit_gracefully(current);
		if (pid == 0)
		{
			fd_handling2(current, get_head_node(current));
			forkflag = 0;
		}
	}
	if (forkflag == 0)
		status = builtin_ladder(status, current, pid);
	return (status);
}

void	execute_system_command(t_list *current, char **g_envcpy, \
t_list *head)
{
	pid_t	pid;

	pid = fork();
	init_child_signals();
	if (pid == -1)
		exitmsg("fork fail\n");
	else if (pid == 0)
	{
		fd_handling2(current, head);
		if (execve(current->value, current->args, g_envcpy) == -1)
		{
			ft_putstr_fd("shelly: ", 2);
			ft_putstr_fd(current->value, 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		exit(1);
	}
}

int	runcmd(t_list *head, char **g_envcpy)
{
	t_list	*current;
	pid_t	pid;
	int		status;

	init_runcmd(&current, &status, &pid, &head);
	while (current)
	{
		if (execflag_check(&current) == 1)
			continue ;
		if (current->value == NULL)
			cmd_not_found_update_status(current, &status);
		else if (slash_check(current->value) == 1 && \
		current->system_command != 1)
		{
			if (runcmd_directory_check(&status, &current) == 1)
				continue ;
		}
		else if (is_it_builtin(current->value) > 0)
			status = execute_builtin(current);
		else if (current->system_command == 1)
			execute_system_command(current, g_envcpy, head);
		current = current->next;
	}
	current = head;
	return (end_runcmd(&current, &head, status, pid));
}
