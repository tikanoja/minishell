/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:20:27 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 14:19:43 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_definer(char *arg)
{
	int	j;
	int	seen_n;

	j = 1;
	seen_n = 0;
	if (!arg)
		return (0);
	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		if (arg[2] != 'n' && arg[2] == '\0')
			return (1);
		while (arg[j] == 'n')
		{
			j++;
			if (arg[j] == '\0')
				return (1);
			if (arg[j] != 'n')
				seen_n = 1;
			else if (seen_n)
				return (0);
		}
	}
	return (0);
}

int	one_n_checker(t_list *echo)
{
	if (echo->argc < 1)
		return (printf("\n"));
	if (echo->argc == 1)
	{
		if (n_definer(echo->args[0]) == 1)
			return (1);
		else
			return (0);
	}
	return (0);
}

char	*create_echo_str(t_list *echo, int j, int i, int n_flag)
{
	int		len;
	char	*str;

	len = 0;
	while (echo->args[j])
	{
		len += ft_strlen(echo->args[j]);
		j++;
	}
	str = ft_calloc(len + echo->argc, sizeof(char));
	if (str == NULL)
		exit_gracefully(echo);
	ft_strcat(str, echo->args[i]);
	i++;
	while (i < echo->argc)
	{
		ft_strcat(str, " ");
		ft_strcat(str, echo->args[i]);
		i++;
	}
	printf("%s", str);
	if (n_flag == 0)
		printf("\n");
	return (str);
}

int	ft_echo(t_list *echo)
{
	int		n_flag;
	char	*string;
	int		len;
	int		original_fd;

	n_flag = 0;
	len = 0;
	if (echo->argc == 0)
	{
		printf("\n");
		return (0);
	}
	if (one_n_checker(echo) == 1)
		return (0);
	while (n_definer(echo->args[n_flag]) == 1)
		n_flag++;
	if (echo->argc <= n_flag)
		return (0);
	original_fd = dup(STDOUT_FILENO);
	dup2(echo->output, STDOUT_FILENO);
	string = create_echo_str(echo, n_flag, n_flag, n_flag);
	dup2(original_fd, STDOUT_FILENO);
	close(original_fd);
	free (string);
	return (0);
}
