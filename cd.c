#include "minishell.h"

/*int ft_cd(const char *user_path, int argc, char **envp) //palauttaako varmasti int, pitäisköhän niiden ENV:ien olla jossain globaalissa vai miten toimii
{
	char *path;
	char *oldpwd;

	path = (char *)malloc(sizeof(char) * ft_strlen(user_path) + 1);
	path = user_path;
	//oldpwd = $PWD; 
	if (argc == 0 || *path == 126) //tyhjä input vaihtaa kotiin, myös ~ vaihtaa kotiin?
		path = ;//ENV $HOME?
	else if (*path == 46) // 46 = '.'
		path = ;//ENV $PWD?
	else if(*path == 46 && *(path + 1) == 46) // onks vähän ratchett
		path = ;//ENV $PWD - eka sana until '/' duunaa joku PWD cutter?
	else if (ft_strncmp(user_path, "$OLDPWD", 7) == 0 || *user_path == 45) //45 = '-', 7 strncmp koska toi ENV on 7 pitkä
		path = ; //ENV $OLDPWD
	//pitääkö PWD päivittää kaipa?
	if(chdir(path) != 0)
		printf("cd: %s: No such file or directory\n", path); //mikä error tähän?
	//ENV PWD = path;?
}*/

#include <limits.h>
char *ft_strcat(char *dest, const char *src)
{
    // Save a pointer to the start of dest
    char *result; 
	
	result = dest;
    while (*dest != '\0')
        dest++;
    while (*src != '\0')
	{
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return result;
}
char *my_realpath(const char *path, char *resolved_path)
{
    char cwd[PATH_MAX];
    char *p;

    if (!path || !resolved_path)
	{
        //errno = EINVAL;
        return (NULL);
    }
    if (path[0] == '/')
	{ // absolute path
    	ft_strlcpy(resolved_path, path, PATH_MAX);
        resolved_path[PATH_MAX - 1] = '\0';
    }
	else
	{ // relative path
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

int ft_cd(const char *user_path, int argc) 
{
    char *path;
    char *oldpwd;
    char cwd[1024]; //current working directory
	char *last_slash;

    path = (char *)malloc(sizeof(char) * (ft_strlen(user_path) + 1));
    if (!path)
	{
        perror("malloc failed");
        return (-1);
    }
    ft_strlcpy(path, user_path, ft_strlen(user_path));
    if (argc == 0 || *path == '~')
        path = getenv("HOME");
	else if (*path == '.')
	{
        if (*(path + 1) == '/')
		{
            getcwd(cwd, sizeof(cwd));
            ft_strcat(cwd, "/");
            ft_strcat(cwd, path);
            path = my_realpath(cwd, NULL);
        }
		else if (*(path + 1) == '\0')
            path = getenv("PWD");
		else if (*(path + 1) == '.' && *(path + 2) == '/') //näitä pitää varmaan vähän rukata
		{
            getcwd(cwd, sizeof(cwd));
            last_slash = ft_strrchr(cwd, '/');
            *last_slash = '\0';
            ft_strcat(cwd, "/");
            ft_strcat(cwd, path + 2);
            path = my_realpath(cwd, NULL);
        }
    }
	else if (ft_strncmp(user_path, "$OLDPWD", 7) == 0 || *user_path == '-')
        path = getenv("OLDPWD");
    oldpwd = getenv("PWD");
    if(chdir(path) != 0)
	{
        perror(path);
        return -1;
    }
    setenv("OLDPWD", oldpwd, 1);
    setenv("PWD", getcwd(cwd, sizeof(cwd)), 1);
	free(path);
    return (0);
}
/*
int main(int argc, char **argv, char **envp) {
    char path[PATH_MAX];
    char resolved_path[PATH_MAX];
    printf("PATH_MAX = %d\n", PATH_MAX);

    // Test my_realpath() function
    printf("Enter a path to resolve: ");
    scanf("%s", path);
    if (my_realpath(path, resolved_path) == NULL) {
        perror("my_realpath() failed");
        exit(EXIT_FAILURE);
    }
    printf("Resolved path: %s\n", resolved_path);

    // Test ft_cd() function
    char *home_dir = getenv("HOME");
    if (ft_cd(home_dir, 0, envp) != 0) {
        perror("ft_cd() failed");
        exit(EXIT_FAILURE);
    }
    printf("Current working directory after cd to HOME: %s\n", getcwd(NULL, 0));
    return 0;
}*/