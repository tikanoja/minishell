/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:18:50 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/29 23:37:25 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_operator(char *str)
{
	if (is_it_redirection > 0)
		return (is_it_redirection(str));
	else if (is_it_log_operator > 0)
		return (is_it_log_operator(str));
	return (0);
}

int	get_token_len(char *str)
{
	int	len;

	len = 0;
	if (*str == '\'' || *str == '\"')
		return (handle_quotes(str, *str, 0));
	else if (is_it_operator(str) > 0)
		return (is_it_operator(str));
	else if (is_it_redirection_parsing(str) > 0)
		return (is_it_redirection_parsing(str));
	while (str[len] && str[len] != '\0' && is_it_whitespace(str[len]) == 0 && \
	is_it_log_operator(&str[len]) == 0 && \
	is_it_redirection_parsing(&str[len]) == 0)
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			len = len + handle_quotes(str, str[len], len);
			continue ;
		}
		len++;
	}
	return (len);
}

void	fill_token(int tokenlen, char *token, char *last_str)
{
	int	i;

	i = 0;
	token[tokenlen] = '\0';
	while (i < tokenlen)
	{
		token[i] = last_str[i];
		i++;
	}
}

char	*ft_lexer(char *str, char **g_envcpy, t_list *head)
{
	static char	*last_str;
	char		*token;
	int			tokenlen;

	token = NULL;
	tokenlen = 0;
	if (str != NULL)
		last_str = str;
	while (*last_str && is_it_whitespace(*last_str))
		last_str++;
	if (*last_str == '\0')
		return (NULL);
	tokenlen = get_token_len(last_str);
	token = ft_calloc((tokenlen + 1), sizeof(char));
	if (!token)
		free_env_and_list(g_envcpy, head);
	fill_token(tokenlen, token, last_str);
	last_str = last_str + tokenlen;
	if (*token == '\0')
		return (NULL);
	return (token);
}
