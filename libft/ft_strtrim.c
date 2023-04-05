/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:03:57 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/14 15:30:44 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_index(char const *s1, char const *set)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (i == ft_strlen((char *)s1))
			return (-1);
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
			continue ;
		}
		j++;
	}
	return (i);
}

static int	end_index(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (set[j])
	{
		if (s1[i - 1] == set[j])
		{
			i--;
			j = 0;
			continue ;
		}
		j++;
	}
	return (i);
}

static char	*getempt(void)
{
	char	*empt;

	empt = (char *)malloc(sizeof(char) + 1);
	empt[0] = '\0';
	return (empt);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		sindex;
	int		eindex;
	int		i;
	int		c;

	if (!s1 || !set)
		return (NULL);
	sindex = start_index(s1, set);
	if (sindex == -1)
		return (getempt());
	eindex = end_index(s1, set);
	c = sindex;
	i = 0;
	trim = (char *)malloc(sizeof(char) * (eindex - sindex) + 1);
	if (trim == NULL)
		return (NULL);
	while (i < eindex - sindex)
	{
		trim[i] = s1[c];
		i++;
		c++;
	}
	trim[i] = '\0';
	return (trim);
}
