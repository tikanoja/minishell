/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:00:51 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 20:22:28 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	empty_input(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (is_it_whitespace(str[i]) == 1)
			i++;
		else
			break ;
	}
	if (i == len || len == 0)
		return (1);
	else
		return (0);
}

int	find_next_quote(char quote, int i, char *str)
{
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (-1);
}

int	check_quotes(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			ret = find_next_quote(str[i], i, str);
			if (ret == -1)
			{
				write(2, "unclosed quotes\n", 16);
				return (1);
			}
			i = ret;
		}
		i++;
	}
	return (0);
}

int	return_log_problem(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	check_log_operators(char *prompt)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
		{
			i = find_next_quote(prompt[i], i, prompt) + 1;
			continue ;
		}
		if (ft_strncmp(&prompt[i], "&&", 2) == 0)
			return (return_log_problem("&& not supported\n"));
		if (ft_strncmp(&prompt[i], "||", 2) == 0)
			return (return_log_problem("|| not supported\n"));
		else if (prompt[i] == ';')
			return (return_log_problem("; not supported\n"));
		else if (prompt[i] == '\\')
			return (return_log_problem("\\ not supported\n"));
		else if (prompt[i] == ':')
			return (return_log_problem(": not supported\n"));
		else if (prompt[i] == '#')
			return (return_log_problem("# not supported\n"));
		i++;
	}
	return (0);
}
