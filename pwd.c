#include "minishell.h"

int ft_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd); 
	else
	{
		perror("getcwd() error");
		exit (EXIT_FAILURE);
	}
	return (0);
}