#include "minishell.h"

void	init_heredoc_env_open(int *i, int *j, char **input_opened, char input_env[1024])
{
	(*i) = 0;
	(*j) = 0;
	input_opened = NULL;
	ft_bzero(input_env, 1024);
}

char	*free_heredoc_env_open(char **input, char *input_opened, t_list *current)
{
	free((*input));
	if(input_opened != NULL)
	{
		(*input) = ft_strdup(input_opened);
		if ((*input) == NULL)
			exit_gracefully(current);
	}
	else
		(*input) = NULL;
	free(input_opened);
	return ((*input));
}

void	heredoc_env_open_iterators(char *input, char *input_env, int *i, int *j)
{
	ft_bzero(input_env, (size_t)(*j));
	if (input[(*i)] == '$' || is_it_quote(input[(*i)]) == 0 ||\
	is_it_whitespace(input[(*i)]) == 0)
		(*i)--;
	(*j) = 0;
	return ;
}

void	free_current_and_next(t_list *current)
{
	if (current->next)
		free(current->next->value);
	if (current->next)
		free(current->next);
	free(current->value);
	current->value = NULL;
	free(current);
	current = NULL;
}

void	fill_args_to_prev(t_list *current, t_list *prev, t_list **ret)
{
	int i;

	i = 0;
	while(current->next && current->next->args && current->next->args[i])
	{
		if (prev == NULL)
		{
			prev = add_node(NULL, current->next->args[i], NULL, NULL);
			prev->next = *ret;
			if (*ret != NULL)
				(*ret)->prev = prev;
			current->prev = prev;
			*ret = current->prev;
		}
		else if (prev)
		{
			current->prev->args = realloc_array(current->prev, current->next->args[i]);
			free(current->next->args[i]);
		}
		i++;
	}
}