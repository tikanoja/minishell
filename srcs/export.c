/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:47:52 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_full_valuepair(char **value_pair)
{
	printf("declare -x %s=\"%s\"\n", value_pair[0], value_pair[1]);
	free_valuepair(value_pair);
}

void	print_half_valuepair(char **value_pair)
{
	printf("declare -x %s\n", value_pair[0]);
	free_valuepair(value_pair);
}

int	export_print(int i, t_list *current)
{
	char	**value_pair;

	while (g_envcpy[i] && current->argc == 0)
	{
		value_pair = ft_split(g_envcpy[i], '=');
		if (value_pair == NULL)
			exit_gracefully(current);
		if (value_pair[1])
			print_full_valuepair(value_pair);
		else if (check_if_equal_last(g_envcpy[i]))
			printf("declare -x %s=\"\"\n", value_pair[0]);
		else
			print_half_valuepair(value_pair);
		i++;
	}
	return (0);
}

int	ft_export(t_list *current)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (current->argc == 0)
		return (export_print(i, current));
	while (current->argc > i)
	{
		if (ft_setenv(current->args[i], current) == 1)
			status = 1;
		i++;
	}
	return (status);
}
