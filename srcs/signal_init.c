/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:01:28 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 18:03:28 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_signals(void)
{
	struct sigaction	sa_c;

	sa_c.sa_handler = handle_ctrl_c;
	sigemptyset(&sa_c.sa_mask);
	sa_c.sa_flags = 0;
	sigaction(SIGINT, &sa_c, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	termios_handler(int flag)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	if (flag)
		term.c_lflag &= ~ECHOCTL;
	else
		term.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &term);
	return (0);
}

void	init_child_signals(void)
{
	struct sigaction	sa_c;
	struct sigaction	sa_d;

	sa_c.sa_handler = handle_ctrl_c_child;
	sigemptyset(&sa_c.sa_mask);
	sa_c.sa_flags = 0;
	sigaction(SIGINT, &sa_c, NULL);
	sa_d.sa_handler = handle_ctrl_d_child;
	sigemptyset(&sa_d.sa_mask);
	sa_d.sa_flags = 0;
	sigaction(SIGQUIT, &sa_d, NULL);
	signal(SIGQUIT, handle_ctrl_backslash_child);
}
