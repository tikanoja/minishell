/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:28:46 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 17:07:20 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_special_env_set(const char *value, t_list *current)
{
	char	*key;
	char	**new_env;
	int		found;
	int		row_count;

	found = 0;
	key = ft_strdup(value);
	if (key == NULL)
		exit_gracefully(current);
	key[ft_strlen(key) - 1] = '\0';
	row_count = 0;
	found = special_env_found(current, key, found);
	if (found == 0)
	{
		new_env = copy_env(envcpy, current);
		while (envcpy[row_count] != NULL)
			row_count++;
		free_split(envcpy);
		new_env[row_count - 1] = ft_strjoin((const char *)key, "=\0");
		if (new_env[row_count - 1] == NULL)
				exit_gracefully(current);
		new_env[row_count] = NULL;
		envcpy = new_env;
	}
	free(key);
	return (0);
}


int	do_append_env(char **valuepair,  t_list *current)
{
	char	*key;
	int		found;

	found = 0;
	key = ft_strdup(valuepair[0]);
	if (key == NULL)
		exit_gracefully_free_valuepair(current, valuepair);
	key[ft_strlen(key) - 1] = '\0';
	found = append_found(key, valuepair, found, current);
	if (found == 0)
		append_not_found(current, key, valuepair);
	free(key);
	return (free_valuepair(valuepair));
}

int set_env_found(char **valuepair, const char *value, t_list *current, int *found)
{
	int		env_index;
	size_t	key_len;

	env_index = 0;
	key_len = ft_strlen(valuepair[0]);
	while (envcpy[env_index] != NULL)
	{
		if (ft_strncmp(envcpy[env_index], valuepair[0], key_len) == 0 && \
			(envcpy[env_index][key_len] == '=' || envcpy[env_index][key_len] == '\0'))
		{
			free(envcpy[env_index]);
			envcpy[env_index] = NULL;
			envcpy[env_index] = ft_strdup(value);
			if (envcpy[env_index] == NULL)
				exit_gracefully_free_valuepair(current, valuepair);
			(*found) = 1;
			break ;
		}
		env_index++;
	}
	return (env_index);
}

void	set_env_value(char **valuepair, const char *value, t_list *current)
{
	size_t	env_index;
	int		found;
	char	**new_env;
	
	env_index = 0;
	found = 0;
	env_index = set_env_found(valuepair, value, current, &found);
	if (!found)
	{
		new_env = copy_env(envcpy, current);
		new_env[env_index] = ft_strdup(value);
		if (new_env[env_index] == NULL)
			exit_gracefully_free_valuepair(current, valuepair);
		new_env[env_index + 1] = NULL;
		free_split(envcpy);
		envcpy = new_env;
	}
}
