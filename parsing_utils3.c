#include "minishell.h"

void init_realloc_parsecmd(char ***array, int *i)
{
	(*array) = NULL;
	(*i) = 0;
}

void free_realloc_parsecmd3(char *prompt, char *token, t_list *current, char **array)
{
	int i;
	
	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	free(prompt);
	free(token);
	exit_gracefully(current);
}

void free_realloc_parsecmd2(char *prompt, char *token, t_list *current, char **array)
{
	free(array);
	free(prompt);
	free(token);
	exit_gracefully(current);
}

void free_realloc_parsecmd(char *prompt, char *token, t_list *current)
{
	free(prompt);
	free(token);
	exit_gracefully(current);
}