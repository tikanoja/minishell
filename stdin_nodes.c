/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:04:02 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 21:10:50 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_stdin_input(char *input)
{
	int		start;
	int		end;
	int		i;
	char	*new;

	init_parse_stdin(&start, &end, &i, input);
	while (is_it_whitespace(input[start]) == 1)
		start++;
	while (is_it_whitespace(input[end]) == 1)
		end--;
	if ((size_t)(end - start) == ft_strlen(input) - 1)
		return (input);
	new = ft_calloc(end - start + 1, sizeof(char));
	if (!new)
		return (NULL);
	new[end + 1] = '\0';
	while (start <= end)
	{
		new[i] = input[start];
		i++;
		start++;
	}
	free(input);
	return (new);
}

void	free_fill_node_exit(char **arr, t_list *new, char *input, t_list *curr)
{
	free_split(arr);
	free(new);
	free(input);
	exit_gracefully(curr);
}

void	init_stdin_node(t_list *new, t_list *current)
{
	new->argc = 0;
	new->pipe = 1;
	new->input = STDIN_FILENO;
	new->output = STDOUT_FILENO;
	new->prev = current;
	new->next = NULL;
	new->args = NULL;
	new->execflag = 0;
}

void	free_input_fail(t_list *new, t_list *current)
{
	free(new);
	exit_gracefully(current);
}

t_list	*fill_node_from_stdin(t_list *current)
{
	t_list	*new;
	char	*input;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		exit_gracefully(current);
	init_stdin_node(new, current);
	input = readline(">");
	if (!input)
		return (free_empty_stdin_input(input, new));
	input = parse_stdin_input(input);
	if (!input)
		free_input_fail(new, current);
	if (ft_strlen(input) == 0)
		return (free_empty_stdin_input(input, new));
	if (fill_node_split_check(input) == 1)
		fill_node_from_split(new, input, current);
	else
	{
		new->value = ft_strdup(input);
		if (!new->value)
			free_fill_node_exit(new->args, new, input, current);
		free(input);
	}
	return (new);
}
