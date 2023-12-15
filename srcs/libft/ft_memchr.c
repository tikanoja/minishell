/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:43:47 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:11:52 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			j;
	unsigned char	*sc;
	unsigned char	uc;

	j = 0;
	sc = (unsigned char *)s;
	uc = (unsigned char)c;
	while (j < n)
	{
		if (sc[j] == uc)
			return (&sc[j]);
		j++;
	}
	return (0);
}
