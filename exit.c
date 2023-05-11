#include "minishell.h"
int check_for_non_numeric(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void ft_exit(t_list *exit_arg, int pid)
{
	int exit_status;

	exit_status = 0;
	if (check_for_non_numeric(exit_arg->args[0]) == 1 && exit_arg->argc >= 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", exit_arg->args[0]);
		exit_status = 255;
	}
	else if(exit_arg->argc > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	else if(pid != 0)
		printf("exit\n");
	else if (exit_arg->argc < 1) 
		exit (0);
	else
		exit_status = ft_atoi(exit_arg->args[0]) % 256;
	exit (exit_status);
}
