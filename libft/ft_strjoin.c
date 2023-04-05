/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:35:12 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/14 15:17:41 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*getnew(int s1len, int s2len)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * (s1len + s2len) + 1);
	if (new == NULL)
		return (NULL);
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1len;
	int		s2len;
	int		i;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	i = 0;
	new = getnew(s1len, s2len);
	if (new == NULL)
		return (NULL);
	while (i < s1len)
	{
		new[i] = s1[i];
		i++;
	}
	while (i < s1len + s2len)
	{
		new[i] = s2[i - s1len];
		i++;
	}
	new[i] = '\0';
	return (new);
}
