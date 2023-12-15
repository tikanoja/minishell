/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 14:38:43 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/14 15:12:15 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(char *dup, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	if (dup[i] != '\0')
	{
		while (dup[i] == c && dup[i])
			i++;
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

static char	**getarray(char *dup, char c, int wcount)
{
	int		i;
	char	**arr;

	i = 0;
	arr = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (arr == NULL)
		return (NULL);
	while (i < wcount)
	{
		arr[i] = (char *)malloc(sizeof(char) * (wordlen(dup, c) + 1));
		if (arr == NULL)
			return (NULL);
		i++;
	}
	return (arr);
}

static int	wordcount(const char *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	if (s[0] != c)
		wcount = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			wcount++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		i++;
	}
	return (wcount);
}

static char	**fillarr(char **arr, const char *s, char c, int wcount)
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
			arr[a][b] = s[i];
			b++;
			i++;
		}
		arr[a][b] = '\0';
		a++;
		b = 0;
	}
	arr[wcount] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		wcount;
	char	**arr;
	char	*dup;

	if (s == NULL)
		return (NULL);
	wcount = wordcount(s, c);
	if (*s == '\0' || wcount == 0)
	{
		arr = (char **)malloc(sizeof(char *));
		arr[0] = 0;
		return (arr);
	}
	dup = ft_strdup(s);
	arr = getarray(dup, c, wcount);
	if (arr == NULL)
		return (NULL);
	arr = fillarr(arr, s, c, wcount);
	free(dup);
	return (arr);
}
