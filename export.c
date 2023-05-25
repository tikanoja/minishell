/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:47:52 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/25 17:21:41 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_list *current)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	char **value_pair;
	if (current->argc == 0)
	{
		while (envcpy[i] && current->argc == 0)
		{
			value_pair = ft_split(envcpy[i], '=');
			if(value_pair[1])
			{
				printf("declare -x %s=\"%s\"\n", value_pair[0], value_pair[1]);
				free(value_pair[0]);
				free(value_pair[1]);
				free(value_pair);
			}
			else if (check_if_equal_last(envcpy[i]))
			{
				printf("declare -x %s=\"\"\n", value_pair[0]);
			}
			else
			{
				printf("declare -x %s\n", value_pair[0]);
				free(value_pair[0]);
				free(value_pair);
			}
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
