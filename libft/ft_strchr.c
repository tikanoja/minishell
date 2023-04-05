/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:58:16 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:10:35 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (*ptr != (unsigned char)c)
	{
		if (*ptr == '\0')
		{
			return (NULL);
		}
		ptr++;
	}
	return ((char *)ptr);
}
