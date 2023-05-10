#include "minishell.h"

void ft_exit(t_list *exit_arg, int pid)
{
	int exit_status;
	if(pid != 0)
		printf("exit\n");
	if (exit_arg->argc < 1) 
		exit (0);
	exit_status = ft_atoi(exit_arg->args[0]) % 256;
	exit (exit_status);
}
