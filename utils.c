/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:56:00 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 18:54:17 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_error_sys_cmd(t_list *current)
{
	ft_putstr_fd("shelly: ", 2);
	ft_putstr_fd(current->value, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}
