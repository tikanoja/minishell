/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:52:54 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_valid_key_unset(char *key, int *status, int *flag, int len)
{
	int	index;

	index = 0;
	while (index < len)
	{
		if (check_key_chars(key[index], index) == 0)
		{
			ft_putstr_fd("'", STDERR_FILENO);
			ft_putstr_fd(key, STDERR_FILENO);
			ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
			(*status) = 1;
			(*flag) = 1;
			break ;
		}
		index++;
	}
}

int	find_key_index(char *key, int *i, int flag, int len)
{
	int	index;

	index = -1;
	while (g_envcpy[(*i)] && flag == 0)
	{
		if (ft_strncmp(g_envcpy[(*i)], key, len - 1) == 0 && \
		(g_envcpy[(*i)][len] == '=' || g_envcpy[(*i)][len] == '\0'))
			index = (*i);
		(*i)++;
	}
	return (index);
}

void	unset_g_envcpy(t_list *current, int index, char *key, int i)
{
	char	**new_env;
	int		j;

	new_env = ft_calloc(i, sizeof(char *));
	i = 0;
	j = 0;
	if (new_env == NULL)
		exit_gracefully(current);
	while (g_envcpy[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(g_envcpy[i]);
			if (new_env[j] == NULL)
				exit_gracefully(current);
			j++;
		}
		free(g_envcpy[i]);
		i++;
	}
	new_env[j] = NULL;
	free(g_envcpy);
	g_envcpy = NULL;
	g_envcpy = new_env;
	free(key);
}

int	ft_unsetenv(t_list *current, int k, int len, int status)
{
	int		index;
	int		i;
	char	*key;
	int		flag;

	while (current->args && current->args[k])
	{
		flag = 0;
		key = ft_strdup(current->args[k]);
		if (key == NULL)
			exit_gracefully(current);
		len = ft_strlen(key);
		i = 0;
		check_for_valid_key_unset(key, &status, &flag, len);
		index = find_key_index(key, &i, flag, len);
		if (index == -1)
			free(key);
		else if (flag == 0)
			unset_g_envcpy(current, index, key, i);
		k++;
	}
	return (status);
}
