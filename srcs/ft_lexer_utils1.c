/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:20:50 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 21:21:31 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_whitespace(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	else
		return (0);
}

int	check_token_end(char *str)
{
	if (*str == '\0')
		return (1);
	else if (is_it_whitespace(*str) > 0)
		return (1);
	else if (is_it_redirection_parsing(str) > 0)
		return (1);
	else if (is_it_log_operator(str) > 0)
		return (1);
	return (0);
}

char	get_next_quote(char quote)
{
	if (quote == '\'')
		return ('\'');
	else
		return ('\"');
}

void	init_handle_quotes(int *len, int *quotes, int *start)
{
	(*len) = 1;
	(*quotes) = 1;
	while ((*start) > 0)
	{
		(*len)++;
		(*start)--;
	}
}

void	found_another_quote(char *quote, char *str, int *quotes, int *len)
{
	(*quote) = get_next_quote(str[(*len) + 1]);
	(*quotes)++;
	(*len) = (*len) + 2;
}
