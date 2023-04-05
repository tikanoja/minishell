/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:32:42 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/02/02 17:06:18 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordcount_p(const char *s, char c)
{
	int	wcount;
	int	i;

	wcount = 0;
	i = 0;
	if (s[i] != c)
		wcount = 1;
	while (s[i])
	{
		if (s[i] == 39)
			c = 39;
		if (s[i] == c && s[i + 1] != ' ' && s[i + 1] != 39 && s[i + 1])
		{
			i++;
			while (s[i] != c && s[i])
				i++;
			wcount++;
			c = ' ';
		}
		i++;
	}
	return (wcount);
}

int	wordlen_p(char *dup, char c, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (dup[i] != '\0')
	{
		while ((dup[i] == c && dup[i]) || (dup[i] == 39 && dup[i]))
			i++;
		if (dup[i - 1] == 39)
			c = 39;
		while (dup[i] != c && dup[i])
		{
			i++;
			len++;
		}
	}
	while (j < i)
	{
		dup[j] = c;
		j++;
	}
	return (len);
}

char	**createempty_p(char **arr)
{
	arr = (char **)malloc(sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr[0] = 0;
	return (arr);
}

int	findstring(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}
