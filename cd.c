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

char *ft_realpath(const char *path, char *resolved_path) //
{
	char cwd[PATH_MAX];
	char *p;

	if (!path || !resolved_path)
	{
		//errno = EINVAL;
		return (NULL);
	}
	if (path[0] == '/')
	{ // absolute path aka start with /
		ft_strlcpy(resolved_path, path, PATH_MAX);
		resolved_path[PATH_MAX - 1] = '\0';
	}
	else
	{ // relative path no start with /
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return (NULL);
		ft_strlcpy(resolved_path, cwd, PATH_MAX);
		resolved_path[PATH_MAX - 1] = '\0';
		ft_strlcat(resolved_path, "/", PATH_MAX - ft_strlen(resolved_path) - 1);
		ft_strlcat(resolved_path, path, PATH_MAX - ft_strlen(resolved_path) - 1);
	}
	while ((p = ft_strnstr(resolved_path, "/./", ft_strlen(resolved_path))) != NULL)
		ft_memmove(p + 1, p + 3, ft_strlen(p + 3) + 1);
	while ((p = ft_strnstr(resolved_path, "/../", ft_strlen(resolved_path))) != NULL) 
	{
		if (p == resolved_path)
		{
			//errno = EINVAL;
			return (NULL);
		}
		char *prev_slash = ft_strrchr(resolved_path, '/') - 1;
		ft_memmove(prev_slash, p + 3, ft_strlen(p + 3) + 1);
	}
	return (resolved_path);
}

void ft_cd(t_list *current) //vitusti lisaa error management pitaako ottaa real path kayttoon
{
	int i;
	int path_len;
	char *path;
	char *pwd;
	char *old_pwd;
	char cwd[PATH_MAX];

	i = 0;
	path = current->args[0];
	path_len = ft_strlen(path);
	if(current->argc == 0 || (current->args[0][0] == '~' && current->args[0][1] == '\0'))
	{
		if(chdir(ft_getenv("HOME")) == -1)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
	{
		old_pwd = getcwd(cwd, PATH_MAX);
		old_pwd = ft_strjoin("OLDPWD=", old_pwd);
		//printf("path is %s\n", path);
		if(chdir(path) == -1)
		{
			printf("cd: error\n");
			return ;
		}
		pwd = getcwd(cwd, PATH_MAX);
		pwd = ft_strjoin("PWD=", pwd);
		ft_setenv(old_pwd);
		ft_setenv(pwd);
		//printf("pwd is %s\n", pwd);
		free(pwd);
		free(old_pwd);
		return ;
	}
}
