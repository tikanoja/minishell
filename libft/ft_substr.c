/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:14:12 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/14 15:32:20 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	i = 0;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	slen = ft_strlen((char *)s);
	if (start > slen)
	{
		*sub = '\0';
		return (sub);
	}
	while (i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
