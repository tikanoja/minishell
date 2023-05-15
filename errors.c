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
		i = 0;
		free(current->value);
		while (current->args[i])
		{
			free(current->args[i]);
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

void free_node(t_list *node)
{
	int i;

	i = 0;
	free(node->value);
	while (node->args[i])
	{
		free(node->args[i]);
		i++;
	}
	free(node->args);
	free(node);
}

int     assignment_check(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
