/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:36:26 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:13:33 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*checker(const char *haystack, const char *needle,
unsigned char *ptr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && haystack[i])
	{
		while (haystack[i] == needle[j] && i < len + 1 && haystack[i])
		{
			i++;
			j++;
			if (i > len)
				return (NULL);
			if (!needle[j])
				return ((char *)ptr);
		}
		ptr++;
		i = i - j + 1;
		j = 0;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned char	*ptr;

	if (haystack == NULL && len == 0)
		return (NULL);
	ptr = (unsigned char *)haystack;
	if (needle[0] == '\0')
		return ((char *)ptr);
	if (len > ft_strlen((char *)haystack))
		len = ft_strlen((char *)haystack);
	if (checker(haystack, needle, ptr, len))
		return ((checker(haystack, needle, ptr, len)));
	return (NULL);
}
