/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:47:52 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/22 22:00:54 by jaurasma         ###   ########.fr       */
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
		while (envcpy[i] && current->argc == 0)
		{
			printf("declare -x %s\n", envcpy[i]);
			i++;
		}
		return (0);
	}
	while (current->argc > i)
	{
		if (ft_setenv(current->args[i]) == 1)
			status = 1;
		i++;
	}
	return (status);
}
