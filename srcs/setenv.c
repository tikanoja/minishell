/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:43:35 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 14:59:27 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **env, t_list *current)
{
	size_t	size;
	size_t	i;
	char	**new_env;

	i = 0;
	size = 0;
	while (env[size] != NULL)
		size++;
	new_env = allocate_new_env(size);
	if (new_env == NULL)
		exit_gracefully(current);
	if (new_env == NULL)
	{
		free_split(new_env);
		exit_gracefully(current);
	}
	while (i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
			exit_gracefully_free_valuepair(current, new_env);
		i++;
	}
	return (new_env);
}

int	free_valuepair(char **valuepair)
{
	int	i;

	i = 0;
	while (valuepair[i])
	{
		free(valuepair[i]);
		i++;
	}
	free (valuepair);
	return (0);
}

int	check_if_equal_last(const char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '=' && value[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	setenv_error(char *value, char **valuepair)
{
	ft_putstr_fd("shelly: '", STDERR_FILENO);
	ft_putstr_fd((char *)value, STDERR_FILENO);
	ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
	free_valuepair(valuepair);
	return (1);
}

int	ft_setenv(const char *value, t_list *current)
{
	char	**valuepair;

	valuepair = NULL;
	if (check_if_equal_last(value) == 1)
		return (do_special_env_set(value, current));
	valuepair = ft_split(value, '=');
	if (valuepair == NULL)
		exit_gracefully(current);
	if (valuepair[0] && valuepair[0][ft_strlen(valuepair[0]) - 1] == '+')
		return (do_append_env(valuepair, current));
	if (!ft_strchr(value, '=') && ft_getenv(valuepair[0]))
	{
		free_valuepair(valuepair);
		return (0);
	}
	if (!valuepair[0] || !is_valid_key(valuepair[0]))
		return (setenv_error((char *)value, valuepair));
	set_env_value(valuepair, value, current);
	return (free_valuepair(valuepair));
}
