/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_nodes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:09:48 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 21:10:00 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_empty_stdin_input(char *input, t_list *new)
{
	free(new);
	free(input);
	return (NULL);
}

int	fill_node_split_check(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	fill_node_exit(t_list *new, char *input, char **arr, t_list *current)
{
	free_split(arr);
	free(new);
	free(input);
	exit_gracefully(current);
}

void	fill_node_from_split(t_list *new, char *input, t_list *current)
{
	char	**arr;
	int		i;

	i = 1;
	arr = ft_split(input, ' ');
	if (!arr)
		fill_node_exit(new, input, arr, current);
	free(input);
	new->value = ft_strdup(arr[0]);
	if (!new->value)
		fill_node_exit(new, input, arr, current);
	free(arr[0]);
	while (arr[i])
	{
		new->args = realloc_array(new, arr[i]);
		if (!new->args)
			fill_node_exit(new, input, arr, current);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	init_parse_stdin(int *start, int *end, int *i, char *input)
{
	(*start) = 0;
	(*i) = 0;
	(*end) = ft_strlen(input) - 1;
}
