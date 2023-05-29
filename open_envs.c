/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:43:35 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/27 17:08:34 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar_end(char c)
{
	if (c == '\'' || c == '\"' || c == '<' || c == '>')
		return (1);
	else if (c == '|' || c == '$' || c == '\0')
		return (1);
	else if (is_it_whitespace(c) == 1)
		return (1);
	return (0);
}

int	is_valid_env_char(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	get_env_len(char *str)
{
	int	len;
	int	i;

	len = 0;
	i = 1;
	while (str[i] != '\0' && is_valid_env_char(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

char	*ft_strjoin_oe(char *s1, char *s2, t_list *current)
{
	char	*ns;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	ns = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ns)
		exit_gracefully(current);
	while (s1[i])
		ns[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ns[j++] = s2[i++];
	free(s1);
	ns[j] = '\0';
	return (ns);
}


void	handle_single_quotes(char c, int *flag)
{
	if (c == '\'' && *flag == 0)
		*flag = 1;
	else if (c == '\'' && *flag == 1)
		*flag = 0;
}

int	check_for_quote_dollar(char *str)
{
	if (ft_strncmp(str, "\"$\"", 4) == 0)
		return (0);
	return (1);
}
