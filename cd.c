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

void ft_cd(t_list *current) //vitusti lisaa error management pitaako ottaa real path kayttoon
{
	int i;
	char *path;
	char *pwd;
	char *old_pwd;
	char cwd[PATH_MAX];

	i = 0;
	path = current->args[0];
	//printf("We here!\n");
	if (current->argc == 0 || (current->args[0][0] == '~' && current->args[0][1] == '\0'))
	{
		old_pwd = getcwd(cwd, PATH_MAX);
		old_pwd = ft_strjoin("OLDPWD=", old_pwd);
		if (chdir(ft_getenv("HOME")) == -1)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		pwd = getcwd(cwd, PATH_MAX);
		pwd = ft_strjoin("PWD=", pwd);
		ft_setenv(old_pwd);
		ft_setenv(pwd);
		free(pwd);
		free(old_pwd);
	}
	else if((current->args[0][0] == '-' && current->args[0][1] == '\0'))
	{
		old_pwd = getcwd(cwd, PATH_MAX);
		old_pwd = ft_strjoin("OLDPWD=", old_pwd);
		if (chdir(ft_getenv("OLDPWD")) == -1)
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		pwd = getcwd(cwd, PATH_MAX);
		pwd = ft_strjoin("PWD=", pwd);
		ft_setenv(old_pwd);
		ft_setenv(pwd);
		free(pwd);
		free(old_pwd);
	}
	else
	{
		old_pwd = getcwd(cwd, PATH_MAX);
		old_pwd = ft_strjoin("OLDPWD=", old_pwd);
		if (chdir(path) == -1)
		{
			printf("cd: %s: No such file or directory\n", current->args[0]);
			return ;
		}
		pwd = getcwd(cwd, PATH_MAX);
		pwd = ft_strjoin("PWD=", pwd);
		ft_setenv(old_pwd);
		ft_setenv(pwd);
		free(pwd);
		free(old_pwd);
		return ;
	}
}
