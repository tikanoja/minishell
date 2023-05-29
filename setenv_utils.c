/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:06:37 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 13:09:01 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free_valuepair_string(t_list *current, char **valuepair, char *str)
{
	free(str);
	free_valuepair(valuepair);
	free_env_and_list(envcpy, get_head_node(current));
}

void	exit_gracefully_free_valuepair(t_list *current, char **valuepair)
{
	free_valuepair(valuepair);
	free_env_and_list(envcpy, get_head_node(current));
}

int	check_key_chars(char c, int flag)
{
	if (c >= '0' && c <= '9' && flag)
		return (1);
	else if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c == '_')
		return (1);
	return (0);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (!check_key_chars(key[i], i))
			return (0);
		i++;
	}
	return (1);
}

char	**allocate_new_env(size_t size)
{
	return ((char **)ft_calloc((size + 2), sizeof(char *)));
}
