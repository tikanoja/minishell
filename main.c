/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:37:41 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printlist(t_list *head)
{
	t_list	*current;
	int		i;
	int		j;

	current = head;
	i = 1;
	j = 0;
	while (current != NULL)
	{
		printf("\nNode number %d\n", i);
		printf("value: %s\n", current->value);
		while (current->args && current->args[j] != NULL)
		{
			printf("args: %s\n", current->args[j]);
			j++;
		}
		printf("argc: %d\n", current->argc);
		j = 0;
		printf("in: %d, out: %d\n", current->input, current->output);
		printf("pipeflag: %d\n", current->pipe);
		printf("index: %d\n", current->index);
		printf("system_command: %d\n", current->system_command);
		printf("execlfag: %d\n", current->execflag);
		current = current->next;
		i++;
	}
}

void	add_index(t_list *head)
{
	t_list	*current;
	int		i;

	current = head;
	i = 1;
	while (current)
	{
		current->index = i;
		i++;
		current = current->next;
	}
}

void	ctrl_d_main(void)
{
	printf("exit\n");
	free_env(g_envcpy);
	exit(0);
}

int	main(int argc, char **argv, const char **envp)
{
	int status;

	status = 0;
	if (argc > 1 || argv == NULL)
		exitmsg("too many args");
	get_env_copy(&g_envcpy, envp);
	run_minishell(status);
	return (0);
}
