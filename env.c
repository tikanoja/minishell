/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 14:50:27 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/27 15:46:27 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name)
{
	char	**env;
	size_t	namelen;
	char	*equals;

	env = envcpy;
	namelen = 0;
	while (*env != NULL)
	{
		equals = ft_strchr(*env, '=');
		if (equals != NULL)
		{
			namelen = equals - *env;
			if (ft_strncmp(name, *env, namelen) == 0 && name[namelen] == '\0')
				return (equals + 1);
		}
		env++;
	}
	return (NULL);
}

int	ft_env(t_list *current, int i)
{
	if (current->args)
	{
		if (access(current->args[0], F_OK) == 0)
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(current->args[0], STDERR_FILENO);
			ft_putstr_fd(": Premission denied\n", STDERR_FILENO);
			return (126);
		}
		else
		{
			ft_putstr_fd("env: ", STDERR_FILENO);
			ft_putstr_fd(current->args[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			return (127);
		}
	}
	while (envcpy[i])
	{
		if (ft_strchr(envcpy[i], '='))
			printf("%s\n", envcpy[i]);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
