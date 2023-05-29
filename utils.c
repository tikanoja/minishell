/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:56:00 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 17:34:21 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_failed_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

void	exit_split(char **split, t_list *current)
{
	free_failed_split(split);
	exit_gracefully(current);
}

void	print_error_sys_cmd(t_list *current)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(current->value, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
