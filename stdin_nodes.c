#include "minishell.h"

void	*free_empty_stdin_input(char *input, t_list *new)
{
	free(new);
	free(input);
	return(NULL);
}

int fill_node_split_check(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void fill_node_from_split(t_list *new, char *input, t_list *current)
{
	char **arr;
	int i;

	i = 1;
	arr = ft_split(input, ' ');
	if (!arr)
	{
		free_split(arr);
		exit_gracefully(current);
	}
	free(input);
	new->value = ft_strdup(arr[0]);
	if (!new->value)
	{
		free_split(arr);
		exit_gracefully(current);
	}
	free(arr[0]);
	while(arr[i])
	{
		new->args = realloc_array(new, arr[i], NULL, NULL); // mita jos pitaa fill useempi node?
		if (!new->args)
			exit_gracefully(current);
		free(arr[i]);
		i++;
	}
	free(arr);
}

char *parse_stdin_input(char *input, t_list *current)
{
	int start;
	int end;
	int i;
	char *new;

	start = 0;
	end = ft_strlen(input) - 1;
	i = 0;
	while(is_it_whitespace(input[start]) == 1)
		start++;
	while(is_it_whitespace(input[end]) == 1)
		end--;
	if ((size_t)(end - start) == ft_strlen(input) - 1)
		return(input);
	new = ft_calloc(end - start + 1, sizeof(char));
	if (!new)
		exit_gracefully(current);
	new[end + 1] = '\0';
	while (start <= end)
	{
		new[i] = input[start];
		i++;
		start++;
	}
	free(input);
	return(new);
}

t_list	*fill_node_from_stdin(t_list *current)
{
	t_list *new;
	char *input;
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		exit_gracefully(current);
	new->argc = 0;
	new->pipe = 1;
	new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
	new->prev = current;
	new->next = NULL;
	new->args = NULL;
	new->execflag = 0;
	input = readline(">"); // ehk pitaa lisaa splitti!
	input = parse_stdin_input(input, current);
	if (ft_strlen(input) == 0)
		return (free_empty_stdin_input(input, new));
	if (fill_node_split_check(input) == 1)
		fill_node_from_split(new, input, current);
	else
	{
		new->value = ft_strdup(input);
		if (!new->value)
			exit_gracefully(current);
		free(input);
	}
	return (new);
}