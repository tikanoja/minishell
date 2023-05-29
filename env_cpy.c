/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:03:13 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_env_copy(char ***g_envcpy, const char **envp, int rows, int i)
{
	while (envp[rows] != NULL)
		rows++;
	(*g_envcpy) = ft_calloc((rows + 1), sizeof(char *));
	if (!g_envcpy)
		exitmsg("g_envcpy malloc fail");
	(*g_envcpy)[rows] = NULL;
	while (i < rows)
	{
		(*g_envcpy)[i] = ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
		if ((*g_envcpy)[i] == NULL)
		{
			i = 0;
			while ((*g_envcpy)[i] != NULL)
			{
				free((*g_envcpy)[i]);
				i++;
			}
			free((*g_envcpy));
			exitmsg("env copy malloc failed");
		}
		(*g_envcpy)[i][ft_strlen(envp[i])] = '\0';
		i++;
	}
}

void	get_env_copy(char ***g_envcpy, const char **envp)
{
	int	i;
	int	j;
	int	rows;

	i = 0;
	j = 0;
	rows = 0;
	while (envp[rows] != NULL)
		rows++;
	malloc_env_copy(g_envcpy, envp, rows, i);
	while (envp[i])
	{
		(*g_envcpy)[i][j] = envp[i][j];
		j++;
		if (envp[i][j] == '\0')
		{
			i++;
			j = 0;
		}
	}
}
