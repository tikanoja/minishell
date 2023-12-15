/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:53:44 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:07:30 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	move(size_t len, unsigned char *srcc, unsigned char *dstc)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dstc[i] = srcc[i];
		i++;
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*srcc;
	unsigned char	*dstc;

	srcc = (unsigned char *)src;
	dstc = (unsigned char *)dst;
	if (dstc == 0 && srcc == 0)
		return (0);
	if (dstc > srcc)
	{
		while (len > 0)
		{
			dstc[len - 1] = srcc[len - 1];
			len--;
		}
	}
	else
		move(len, srcc, dstc);
	return (dst);
}
