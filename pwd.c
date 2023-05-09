#include "minishell.h"

void ft_pwd()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd); 
	else
	{
		perror("getcwd() error");
		exit (EXIT_FAILURE);
	}
}