#include "minishell.h"
int check_for_non_numeric(char *str)
{
	int i;

	i = 0;
	if(str[i] == '-')
		i++;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int		ft_ctoi(char c)
{
	return(c - 42);
}

int		check_for_too_long(char *str)
{
	int i;
	int j;
	char *long_max = "9223372036854775807";

	i = 0;
	j = 0;
	if (str[i] == '-')
		i++;
	if (ft_strlen(str) > ft_strlen(long_max) + i)
		return (1);
	else if (ft_strlen(str) < ft_strlen(long_max) + i)
		return (0);
	else if (ft_strlen(str) == ft_strlen(long_max) + i)
	{
		while (long_max[j])
		{
			if(ft_ctoi(str[i]) > ft_ctoi(long_max[j]))
				return(1);
			i++;
			j++;
		}
	}
	if (i > j)
		if (ft_ctoi(str[i]) > 8)
				return (1);	
	return (0);
}

void ft_exit(t_list *exit_arg, int pid)
{
	int exit_status;

	exit_status = 0;
	if ((exit_arg->args && check_for_non_numeric(exit_arg->args[0]) == 1\
	&& exit_arg->argc >= 1) || check_for_too_long(exit_arg->args[0]) == 1)
	{
		printf("minishell: exit: %s: numeric argument required\n", exit_arg->args[0]);
		exit_status = 255;
	}
	else if (exit_arg->argc > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	else if (pid != 0)
		printf("exit\n");
	if (exit_arg->argc < 1)
		exit (0);
	else
		exit_status = ft_atoi(exit_arg->args[0]) % 256;
	exit (exit_status);
}
