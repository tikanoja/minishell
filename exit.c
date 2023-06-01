/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:58:16 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 19:29:07 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_non_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_ctoi(char c)
{
	return (c - 42);
}

int	check_for_too_long(char *str, int i, int j)
{
	char	*long_max;

	long_max = "9223372036854775807";
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_strlen(str) > ft_strlen(long_max) + i)
		return (1);
	else if (ft_strlen(str) < ft_strlen(long_max) + i)
		return (0);
	else if (ft_strlen(str) == ft_strlen(long_max) + i)
	{
		while (long_max[j])
		{
			if (ft_ctoi(str[i++]) > ft_ctoi(long_max[j]))
				return (1);
			j++;
		}
	}
	return (0);
}

void	print_exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	ft_exit(t_list *exit_arg, int pid)
{
	int	exit_status;
	int	flag;

	exit_status = 0;
	flag = 0;
	if ((exit_arg->args && check_for_non_numeric(exit_arg->args[0]) == 1 \
	&& exit_arg->argc >= 1) || \
	(exit_arg->args && check_for_too_long(exit_arg->args[0], 0, 0) == 1))
	{
		print_exit_error(exit_arg->args[0]);
		exit_status = 255;
		flag = 1;
	}
	else if (exit_arg->argc > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (pid != 0)
		printf("exit\n");
	if (exit_arg->argc < 1)
		exit (0);
	else if (flag == 0)
		exit_status = ft_atoi(exit_arg->args[0]) % 256;
	exit (exit_status);
}
