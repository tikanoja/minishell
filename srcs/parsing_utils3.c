/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:54:09 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/05/30 09:54:13 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_realloc_parsecmd(char ***array, int *i)
{
	(*array) = NULL;
	(*i) = 0;
}

void	free_realloc3(char *prompt, char *token, t_list *current, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	free(prompt);
	free(token);
	exit_gracefully(current);
}

void	free_realloc2(char *prompt, char *token, t_list *current, char **array)
{
	free(array);
	free(prompt);
	free(token);
	exit_gracefully(current);
}

void	free_realloc1(char *prompt, char *token, t_list *current)
{
	free(prompt);
	free(token);
	exit_gracefully(current);
}
