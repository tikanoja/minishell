/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 18:30:21 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 12:50:23 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*result;

	result = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (result);
}

int	cd_home(t_list *current)
{
	char	*pwd;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	old_pwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	if (chdir(ft_getenv("HOME")) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	pwd = getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", pwd);
	ft_setenv(old_pwd, current);
	ft_setenv(pwd, current);
	free(pwd);
	free(old_pwd);
	return (0);
}

int	cd_back(t_list *current)
{
	char	*pwd;
	char	*old_pwd;
	char	cwd[PATH_MAX];
	int		status;

	old_pwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	status = 0;
	if (chdir(ft_getenv("OLDPWD")) == -1)
	{
		ft_putstr_fd("shelly: cd: ", STDERR_FILENO);
		perror("OLDPWD not set");
		free(old_pwd);
		status = errno;
		return (status);
	}
	pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX));
	ft_setenv(old_pwd, current);
	ft_setenv(pwd, current);
	free(pwd);
	free(old_pwd);
	return (status);
}

int	cd_path(char *path, t_list *current)
{
	char	*pwd;
	char	*old_pwd;
	char	cwd[PATH_MAX];
	int		status;

	old_pwd = ft_strjoin("OLDPWD=", getcwd(cwd, PATH_MAX));
	status = 0;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("shelly: cd: ", STDERR_FILENO);
		ft_putstr_fd(current->args[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
		free(old_pwd);
		status = errno;
		return (status);
	}
	pwd = ft_strjoin("PWD=", getcwd(cwd, PATH_MAX));
	ft_setenv(old_pwd, current);
	ft_setenv(pwd, current);
	free(pwd);
	free(old_pwd);
	return (status);
}

int	ft_cd(t_list *current)
{
	char	*path;
	int		status;

	path = NULL;
	status = 0;
	if (current->argc > 0)
		path = ft_strdup(current->args[0]);
	if (current->argc == 0 || (path[0] == '~' && path[1] == '\0'))
		status = cd_home(current);
	else if ((path[0] == '-' && path[1] == '\0'))
		status = cd_back(current);
	else
		status = cd_path(path, current);
	if (path)
		free(path);
	return (status);
}
