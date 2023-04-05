/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:32:54 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/02/02 17:04:21 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**getarray_p(char *dup, char c, int wcount)
{
	int		i;
	char	**arr;
	int		len;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (arr == NULL)
		return (NULL);
	while (i < wcount)
	{
		len = 0;
		arr[i] = (char *)malloc(sizeof(char) * (wordlen_p(dup, c, len) + 1));
		if (arr == NULL)
			return (NULL);
		i++;
	}
	arr[wcount] = NULL;
	i = 0;
	while (arr[0][i])
	{
		arr[0][i] = '\0';
		i++;
	}
	return (arr);
}

int	fillhelper2(const char *s, size_t *i, char *c)
{
	int	ret;

	ret = 0;
	if (*s == 39 && *c == 39)
	{
		(*i)++;
		*c = ' ';
		ret = 1;
	}
	else if (*s == 39 && *c == ' ')
	{
		(*i)++;
		*c = 39;
		ret = 1;
	}
	return (ret);
}

void	fillhelper(char *arr, int *b, size_t *i, char *c)
{
	if (*c == 39)
	{
		(*i)++;
		*c = ' ';
	}
	*(arr + 1) = '\0';
	*b = 0;
}

char	**fillarr_p(char **arr, const char *s, char c, int wcount)
{
	int		a;
	int		b;
	size_t	i;

	a = 0;
	b = 0;
	i = 0;
	while (s[i] && a <= wcount - 1)
	{
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			if (fillhelper2(&s[i], &i, &c) == 1)
				continue ;
			arr[a][b] = s[i];
			b++;
			i++;
		}
		fillhelper(&arr[a][b], &b, &i, &c);
		a++;
	}
	arr[wcount] = NULL;
	return (arr);
}

char	**ft_split_p(char const *s, char c)
{
	int		wcount;
	char	**arr;
	char	*dup;

	arr = NULL;
	if (s == NULL)
		return (NULL);
	wcount = wordcount_p(s, c);
	if (*s == '\0' || wcount == 0)
	{
		arr = createempty_p(arr);
		return (arr);
	}
	dup = ft_strdup(s);
	if (dup == NULL)
		return (NULL);
	arr = getarray_p(dup, c, wcount);
	if (arr == NULL)
		return (NULL);
	arr = fillarr_p(arr, s, c, wcount);
	free(dup);
	return (arr);
}
