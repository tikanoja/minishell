/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 18:43:35 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/27 20:37:21 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_setenv(char **env)
{
	size_t	i;

	i = 0;
	if (env == NULL)
		return ;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char **copy_env(char **env)
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
	{
		while (i < size) 
		{
			free(new_env[i]);
			i++;
		}
		return (NULL);
	}
	while (i < size) {
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL) 
		{
			while (i > 0)
			{
				free(new_env[i-1]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

void	set_env_value(char **env, const char *key, const char *value)
{
	size_t	key_len;
	size_t	env_index;
	int		found;
	char	**new_env;
	
	key_len = ft_strlen(key);
	env_index = 0;
	found = 0;
	while (env[env_index] != NULL)
	{
		if (ft_strncmp(env[env_index], key, key_len) == 0 && \
			(env[env_index][key_len] == '=' || env[env_index][key_len] == '\0'))
		{
			free(env[env_index]);
			env[env_index] = NULL;
			env[env_index] = ft_strdup(value);
			found = 1;
			break ;
		}
		env_index++;
	}
	if (!found)
	{
		new_env = copy_env(envcpy);
		new_env[env_index] = ft_strdup(value);
		new_env[env_index + 1] = NULL;
		free_setenv(envcpy);
		envcpy = new_env;
	}
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

int	do_special_env_set(const char *value)
{
	char	*key;
	char	**new_env;
	size_t	env_index;
	size_t	key_len;
	int		found;
	int		row_count;

	env_index = 0;
	found = 0;
	key = ft_strdup(value);
	key[ft_strlen(key) - 1] = '\0';
	key_len = ft_strlen(key);
	row_count = 0;
	while (envcpy[env_index])
	{
		if (ft_strncmp(envcpy[env_index], key, key_len) == 0 && \
		envcpy[env_index][key_len] == '=')
		{
			free(envcpy[env_index]);
			envcpy[env_index] = ft_strjoin((const char *)key, "=\0");
			found = 1;
			break ;
		}
		env_index++;
	}
	if (found == 0)
	{
		new_env = copy_env(envcpy);
		while (envcpy[row_count] != NULL)
			row_count++;
		free_setenv(envcpy);
		new_env[row_count - 1] = ft_strjoin((const char *)key, "=\0");
		new_env[row_count] = NULL;
		envcpy = new_env;
	}
	free(key);
	return (0);
}

int append_found(char *key, char *key_value, int found)
{
	size_t	env_index;
	size_t	key_len;
	char	*appended;

	env_index = 0;
	key_len = ft_strlen(key);
	while (envcpy[env_index])
	{
		if (ft_strncmp(envcpy[env_index], key, key_len) == 0 \
		&& envcpy[env_index][key_len] == '=')
		{
			appended = ft_strdup(envcpy[env_index]);
			free(envcpy[env_index]);
			envcpy[env_index] = ft_strjoin(appended, key_value);
			found = 1;
			free(appended);
			break ;
		}
		env_index++;
	}
	return (found);
}

int	do_append_env(char **valuepair)
{
	char	*key;
	char	*appended = NULL;
	char	**new_env;
	size_t	env_index;
	int		found;
	int		row_count;

	env_index = 0;
	found = 0;
	key = ft_strdup(valuepair[0]);
	key[ft_strlen(key) - 1] = '\0';
	row_count = 0;
	found = append_found(key, valuepair[1], found);
	if (found == 0)
	{
		new_env = copy_env(envcpy);
		while (envcpy[row_count] != NULL)
			row_count++;
		free_setenv(envcpy);
		appended = ft_strjoin((const char *)key, "=");
		appended = ft_strjoin_oe(appended, valuepair[1]);
		new_env[row_count] = ft_strdup(appended);
		new_env[row_count + 1] = NULL;
		envcpy = new_env;
		free(appended);
	}
	free(key);
	return (free_valuepair(valuepair));
}

int	setenv_error(char *value, char **valuepair)
{
	ft_putstr_fd("shelly: '", STDERR_FILENO);
	ft_putstr_fd((char *)value, STDERR_FILENO);
	ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
	free_valuepair(valuepair);
	return (1);
}

int	underscore_env_set(char *value, char **valuepair)
{
	size_t	row_count;

	row_count = 0;
	while (envcpy[row_count] != NULL)
		row_count++;
	envcpy[row_count - 1] = ft_strdup(value);
	envcpy[row_count] = NULL;
	return (free_valuepair(valuepair));
}

int	ft_setenv(const char *value)
{
	char	**valuepair;

	valuepair = NULL;
	valuepair = (char **)malloc(2 * sizeof(char *));
	if (check_if_equal_last(value) == 1)
		return (do_special_env_set(value));
	valuepair = ft_split(value, '='); //protect
	if (value == NULL)
		return (1);
	if (valuepair[0] && valuepair[0][ft_strlen(valuepair[0]) - 1] == '+')
		return (do_append_env(valuepair));
	if (!ft_strchr(value, '=') && ft_getenv(valuepair[0]))
	{
		free_valuepair(valuepair);
		return (0);
	}
	if (!valuepair[0] || !is_valid_key(valuepair[0]))
		return (setenv_error((char *)value, valuepair));
	if (ft_strncmp(valuepair[0], "_\0", 2) == 0)
	 	return (underscore_env_set((char *)value, valuepair));
	set_env_value(envcpy, valuepair[0], value);
	return (free_valuepair(valuepair));
}
