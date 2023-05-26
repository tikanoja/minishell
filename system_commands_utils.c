/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_commands_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:52:39 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/26 18:50:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	findpath(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5 * sizeof(char)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	convert_to_lowercase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
}

int	variable_assign_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*get_path(char **patharr, char *cmd)
{
	char	*tmp;
	char	*pathcmd;
	int		i;

	i = 0;
	while (patharr[i])
	{
		tmp = ft_strjoin(patharr[i], "/");
		pathcmd = ft_strjoin(tmp, cmd);
		if (access(pathcmd, F_OK) == 0)
			break ;
		else
		{
			free(tmp);
			free(pathcmd);
			i++;
		}
		if (!patharr[i])
			return (NULL);
	}
	free(tmp);
	return (pathcmd);
}

void	move_value_to_args(t_list *current)
{
	char	**arr;
	int		i;

	i = 0;
	arr = malloc((current->argc + 2) * sizeof(char *));
	if (arr == NULL)
		exit_gracefully(current);
	while (current->argc > 0 && current->args[i])
	{
		arr[i + 1] = ft_strdup(current->args[i]);
		free(current->args[i]);
		i++;
	}
	arr[0] = ft_strdup(current->value);
	if (access(current->value, F_OK) != 0)
		free(current->value);
	if (current->args)
		free(current->args);
	arr[i + 1] = NULL;
	current->args = arr;
}
