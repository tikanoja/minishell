/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_ops_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 17:04:35 by jaurasmaa         #+#    #+#             */
/*   Updated: 2023/05/29 17:48:13 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_env_found(t_list *current, char *key, int found)
{
	size_t	env_index;
	size_t	key_len;

	key_len = ft_strlen(key);
	env_index = 0;
	while (envcpy[env_index])
	{
		if (ft_strncmp(envcpy[env_index], key, key_len) == 0 && \
		envcpy[env_index][key_len] == '=')
		{
			free(envcpy[env_index]);
			envcpy[env_index] = ft_strjoin((const char *)key, "=\0");
			if (envcpy[env_index] == NULL)
				exit_gracefully(current);
			found = 1;
			break ;
		}
		env_index++;
	}
	return (found);
}

int	append_found(char *key, char **valuepair, int found, t_list *current)
{
	size_t	env_index;
	char	*appended;

	env_index = 0;
	while (envcpy[env_index])
	{
		if (ft_strncmp(envcpy[env_index], key, ft_strlen(key)) == 0 \
		&& envcpy[env_index][ft_strlen(key)] == '=')
		{
			appended = ft_strdup(envcpy[env_index]);
			if (appended == NULL)
				exit_gracefully_free_valuepair(current, valuepair);
			free(envcpy[env_index]);
			envcpy[env_index] = NULL;
			envcpy[env_index] = ft_strjoin(appended, valuepair[1]);
			if (envcpy[env_index] == NULL)
				exit_free_valuepair_string(current, valuepair, appended);
			found = 1;
			free(appended);
			break ;
		}
		env_index++;
	}
	return (found);
}

void	append_not_found(t_list *current, char *key, char **valuepair)
{
	char	**new_env;
	char	*appended;
	int		row_count;

	row_count = 0;
	new_env = copy_env(envcpy, current);
	while (envcpy[row_count] != NULL)
		row_count++;
	free_split(envcpy);
	appended = ft_strjoin((const char *)key, "=");
	if (appended == NULL)
		exit_gracefully_free_valuepair(current, valuepair);
	appended = ft_strjoin_oe(appended, valuepair[1]);
	if (appended == NULL)
		exit_gracefully_free_valuepair(current, valuepair);
	new_env[row_count] = ft_strdup(appended);
	if (new_env[row_count] == NULL)
		exit_free_valuepair_string(current, valuepair, appended);
	new_env[row_count + 1] = NULL;
	envcpy = new_env;
	free(appended);
}
