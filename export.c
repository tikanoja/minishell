/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:47:52 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/22 19:49:11 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list *current)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (current->argc == 0)
	{
		while (envcpy[i] && current->argc == 0 && envcpy[i + 1] != NULL)
		{
			printf("declare -x %s\n", envcpy[i]);
			i++;
		}
		return (0);
	}
	while (current->argc > i)
	{
		status = ft_setenv(current->args[i]);
		if (status == 1)
			break ;
		i++;
	}
	return (status);
}
