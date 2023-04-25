#include "minishell.h"

void exitmsg(char *msg)
{
	perror(msg);
	exit(1);
}

void free_list(t_list *head)
{
	t_list	*next;
	t_list	*current;
	int		i;

	current = head;
	i = 0;
	while (current != NULL)
	{
		if (current->input != STDIN_FILENO)
			close(current->input);
		if (current->output != STDOUT_FILENO)
			close(current->output);
		free(current->value);
		while (current->args[i])
		{
			//free(current->args[i]);
			i++;
		}
		free(current->args);
		next = current->next;
		free(current);
		current = next;
	}
}

void free_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void free_env_and_list(char **env, t_list *head)
{
	free_env(env);
	free_list(head);
	exitmsg("malloc failed in parsing");
}

void free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void free_array_and_env(char **array, char **envcpy, t_list *head)
{
	free_array(array);
	free_env_and_list(envcpy, head);
}

// void mallocprotect(t_list *head, int stageflag)
// {
	
//     while (head)
//     {
//         if (head->value)
//         free(head->value);

//         head = head->next;
//     }
// }