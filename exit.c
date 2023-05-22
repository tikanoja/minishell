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

// static int	toolong(int sign)
// {
// 	printf("EN VITTU TAOAHTU\n");
// 	if (sign == 1)
// 		return (-1);
// 	else
// 		return (0);
// }

// long	ft_atol(const char *str)
// {
// 	long long	i;
// 	int			sign;

// 	i = 0;
// 	sign = 1;
// 	while (*str == 32 || (*str >= 9 && *str <= 13))
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			sign = sign * -1;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		i = i * 10 + *str - '0';
// 		printf("%lld\n", i);
// 		if (i > 9223372036854775807)
// 			return (toolong(sign));
// 		str++;
// 	}
// 	return (i * sign);
// }
// int		check_for_too_long(char *str)
// {
// 	int i;

// 	i = 0;
// 	if(ft_strlen(str) > 19)
// 		return(1)
// 	if(ft_strlen(str) == 19 && str[0] != '9')
// 		return (0);
// 	if(ft_strlen(str) == 19 && str[0] == '9')
// 		return (0);	

// 	return (0);
// }
void ft_exit(t_list *exit_arg, int pid)
{
	int exit_status;

	exit_status = 0;
	if (exit_arg->args && check_for_non_numeric(exit_arg->args[0]) == 1\
	&& exit_arg->argc >= 1) //|| check_for_too_long(exit_arg->args[0]) == 1)
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
	if (exit_arg->argc < 1)
		exit (0);
	else
		exit_status = ft_atoi(exit_arg->args[0]) % 256;
	exit (exit_status);
}
