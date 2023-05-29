/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:03:13 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:11:17 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	malloc_env_copy(char ***envcpy, const char **envp, int rows, int i)
{
	while (envp[rows] != NULL)
		rows++;
	(*envcpy) = ft_calloc((rows + 1), sizeof(char *));
	if (!envcpy)
		exitmsg("envcpy malloc fail");
	(*envcpy)[rows] = NULL;
	while (i < rows)
	{
		(*envcpy)[i] = ft_calloc((ft_strlen(envp[i]) + 1), sizeof(char));
		if ((*envcpy)[i] == NULL)
		{
			i = 0;
			while ((*envcpy)[i] != NULL)
			{
				free((*envcpy)[i]);
				i++;
			}
			free((*envcpy));
			exitmsg("env copy malloc failed");
		}
		(*envcpy)[i][ft_strlen(envp[i])] = '\0';
		i++;
	}
}

void	get_env_copy(char ***envcpy, const char **envp)
{
	int	i;
	int	j;
	int	rows;

	i = 0;
	j = 0;
	rows = 0;
	while (envp[rows] != NULL)
		rows++;
	malloc_env_copy(envcpy, envp, rows, i);
	while (envp[i])
	{
		(*envcpy)[i][j] = envp[i][j];
		j++;
		if (envp[i][j] == '\0')
		{
			i++;
			j = 0;
		}
	}
}
