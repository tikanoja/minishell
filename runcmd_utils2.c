#include "minishell.h"

void	close_all_fds(t_list *current)
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

void	init_execute_builtin(pid_t *pid, int *forkflag, int *status)
{
	(*pid) = 1;
	(*forkflag) = 0;
	(*status) = 0;
}

int	slash_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	fd_handling_close_fds(t_list *current)
{
	if (current->input != STDIN_FILENO)
		close(current->input);
	if (current->output != STDOUT_FILENO)
		close(current->output);
}

int	directory_check(char *str)
{
	struct stat	file_info;

	if (stat(str, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
		{
			redir_directory_check_prints(str, 1);
			return (1);
		}
		else if (S_ISREG(file_info.st_mode) && access(str, X_OK) != 0)
		{
			redir_directory_check_prints(str, 2);
			return (1);
		}
	}
	else
	{
		redir_directory_check_prints(str, 3);
		return (1);
	}
	return (0);
}