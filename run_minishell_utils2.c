/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:13:15 by jaurasma          #+#    #+#             */
/*   Updated: 2023/05/30 15:16:23 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stnc(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	check_if_empty_quote(char *str)
{
	int		i;
	char	quote_type;
	int		flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (is_it_whitespace(str[i]) == 1 && flag == 0)
			i++;
		if ((str[i] == '\"' || str[i] == '\'') && flag == 0)
		{
			quote_type = str[i];
			flag = 1;
			i++;
		}
		if (flag == 1 && (is_it_whitespace(str[i]) == 1 || \
		str[i] == quote_type))
			i++;
		else
			return (1);
	}
	return (0);
}
