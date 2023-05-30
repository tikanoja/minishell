/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 19:55:42 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 16:54:07 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_main_signals(void)
{
	init_signals();
	termios_handler(1);
}

char	*get_prompt(char *prompt)
{
	init_main_signals();
	prompt = readline("\033[0;32mshelly\033[0m> ");
	if (!prompt)
		ctrl_d_main();
	termios_handler(0);
	if (prompt[0] != '\0')
		add_history(prompt);
	return (prompt);
}

int	check_if_head_ok(t_list *head)
{
	if (head == NULL || !head || !head->value || *head->value == '\0')
	{
		if (head)
		{
			while (head && !head->value)
				head = head->next;
		}
		if (!head || *head->value == '\0')
			return (1);
	}
	return (0);
}

int	prompt_if_check(char *prompt, int *status)
{
	if (empty_input(prompt) == 0 && check_quotes(prompt, 1) == 0 && \
	check_if_empty_quote(prompt) == 0)
	{
		ft_putstr_fd("shelly: : command not found\n", 2);
		free(prompt);
		(*status) = 127;
		return (1);
	}
	if (empty_input(prompt) == 0 && check_quotes(prompt, 1) == 0 && \
	check_for_empty_redir(prompt) == 1)
	{
		free(prompt);
		(*status) = 127;
		return (1);
	}
	if (check_quotes(prompt, 0) == 1 || empty_input(prompt) == 1 || \
	check_log_operators(prompt) == 1)
	{
		free(prompt);
		(*status) = 1;
		return (1);
	}
	return (0);
}

void	run_minishell(void)
{
	char	*prompt;
	t_list	*head;
	int		status;

	prompt = NULL;
	head = NULL;
	status = 0;
	while (1)
	{
		prompt = get_prompt(prompt);
		if (prompt_if_check(prompt, &status) == 1)
			continue ;
		head = parsecmd(prompt, g_envcpy);
		if (double_redir_check(head, &status) == 1)
			continue ;
		head = gatekeeper(head, status);
		head = open_fds_and_pipes(head);
		printlist(head);
		if (check_if_head_ok(head) == 1)
			continue ;
		parse_system_commands(head, 0);
		head = get_head_node(head);
		add_index(head);
		status = runcmd(head, g_envcpy);
		free_list(head);
	}
}
