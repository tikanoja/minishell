/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 22:45:23 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 22:49:52 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_list *current)
{
	int	i;

	i = 0;
	while (current->args && current->args[i])
	{
		if (current->args[i])
			free(current->args[i]);
		current->args[i] = NULL;
		i++;
	}	
}

void	free_list(t_list *head)
{
	t_list	*next;
	t_list	*current;

	next = NULL;
	current = head;
	while (current != NULL)
	{
		if (current->value)
			free(current->value);
		free_args(current);
		if (current->args)
			free(current->args);
		if (current->input != STDIN_FILENO)
			close(current->input);
		if (current->output != STDOUT_FILENO)
			close(current->output);
		next = current->next;
		if (current)
			free(current);
		current = NULL;
		current = next;
	}
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (env[i])
			free(env[i]);
		i++;
	}
	free(env);
}

void	free_env_and_list(char **env, t_list *head)
{
	free_env(env);
	free_list(head);
	exitmsg("malloc failed\n");
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
