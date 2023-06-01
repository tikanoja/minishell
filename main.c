/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:37:41 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/31 11:00:42 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr_fd("exit\n", 2);
	free_env(g_envcpy);
	exit(0);
}

int	main(int argc, char **argv, const char **envp)
{
	int	status;

	status = 0;
	if (argc > 1 || argv == NULL)
		exitmsg("too many args");
	get_env_copy(&g_envcpy, envp);
	run_minishell(status);
	return (0);
}
