#include "minishell.h"
#include <limits.h> //tän vois vissiin vaan definaa PATH_MAX 1024?

char *ft_strcat(char *dest, const char *src)
{
	char *result; 
	
	result = dest;
	while (*dest != '\0')
		dest++;
	while (*src != '\0')
		*dest++ = *src++;
	*dest = '\0';
	return (result);
}

int cd_home(void)
{
	char *pwd;
	char *old_pwd;
	char cwd[PATH_MAX];
	
	old_pwd = getcwd(cwd, PATH_MAX);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (chdir(ft_getenv("HOME")) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (1);
	}
	pwd = getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", pwd);
	ft_setenv(old_pwd);
	ft_setenv(pwd);
	free(pwd);
	free(old_pwd);
	return(0);
}

int cd_back(void)
{
	char *pwd;
	char *old_pwd;
	char cwd[PATH_MAX];

	old_pwd = getcwd(cwd, PATH_MAX);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (chdir(ft_getenv("OLDPWD")) == -1)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	pwd = getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", pwd);
	ft_setenv(old_pwd);
	ft_setenv(pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

int cd_path(char *path, t_list *current)
{
	char *pwd;
	char *old_pwd;
	char cwd[PATH_MAX];
	old_pwd = getcwd(cwd, PATH_MAX);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("shelly: cd: ", STDERR_FILENO);
		ft_putstr_fd(current->args[0], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	pwd = getcwd(cwd, PATH_MAX);
	pwd = ft_strjoin("PWD=", pwd);
	ft_setenv(old_pwd);
	ft_setenv(pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

int ft_cd(t_list *current) //vitusti lisaa error management pitaako ottaa real path kayttoon
{
	char *path;
	int	status;
	
	path = NULL;
	status = 0;
	if(current->argc > 0)
		path = ft_strdup(current->args[0]);
	if (current->argc == 0 || (path[0] == '~' && path[1] == '\0'))
		status = cd_home();
	else if((path[0] == '-' && path[1] == '\0'))
		status = cd_back();
	else
		status = cd_path(path, current);
	if (path)
		free(path);
	return (status);
}

	// {
	// 	old_pwd = getcwd(cwd, PATH_MAX);
	// 	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	// 	if (chdir(ft_getenv("HOME")) == -1)
	// 	{
	// 		free(old_pwd);
	// 		if(current->argc > 0)
	// 			free(path);
	// 		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
	// 		return ;
	// 	}
	// 	pwd = getcwd(cwd, PATH_MAX);
	// 	pwd = ft_strjoin("PWD=", pwd);
	// 	ft_setenv(old_pwd);
	// 	ft_setenv(pwd);
	// 	free(pwd);
	// 	free(old_pwd);
	// 	if(current->argc > 0)
	// 		free(path);
	// }
	// {
	// 	// old_pwd = getcwd(cwd, PATH_MAX);
	// 	// old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	// 	// if (chdir(ft_getenv("OLDPWD")) == -1)
	// 	// {
	// 	// 	ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
	// 	// 	free(old_pwd);
	// 	// 	free(path);
	// 	// 	return ;
	// 	// }
	// 	// pwd = getcwd(cwd, PATH_MAX);
	// 	// pwd = ft_strjoin("PWD=", pwd);
	// 	// ft_setenv(old_pwd);
	// 	// ft_setenv(pwd);
	// 	// free(pwd);
	// 	// free(old_pwd);
	// }
	// {
	// 	old_pwd = getcwd(cwd, PATH_MAX);
	// 	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	// 	if (chdir(path) == -1)
	// 	{
	// 		ft_putstr_fd("shelly: cd: ", STDERR_FILENO);
	// 		ft_putstr_fd(current->args[0], STDERR_FILENO);
	// 		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	// 		free(old_pwd);
	// 		free(path);
	// 		return ;
	// 	}
	// 	pwd = getcwd(cwd, PATH_MAX);
	// 	pwd = ft_strjoin("PWD=", pwd);
	// 	ft_setenv(old_pwd);
	// 	ft_setenv(pwd);
	// 	free(pwd);
	// 	free(old_pwd);
	// 	free(path);
	// }