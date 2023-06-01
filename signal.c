/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:14:17 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 18:03:33 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signum __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_c_child(int signum __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
}

void	handle_ctrl_d_child(int signum __attribute__((unused)))
{
	write(STDERR_FILENO, "\n", 1);
}

void	handle_ctrl_backslash_child(int signum __attribute__((unused)))
{
	write(STDERR_FILENO, "Quit: 3\n", 9);
}
