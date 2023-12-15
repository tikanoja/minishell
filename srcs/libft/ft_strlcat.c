/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:06:35 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:08:51 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	ans;
	size_t	ogdst;

	i = 0;
	ans = 0;
	srclen = ft_strlen((char *)src);
	if (dst == NULL && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	ogdst = ft_strlen(dst);
	if (dstsize >= dstlen)
		ans = dstlen + srclen;
	else
		return (srclen + dstsize);
	while (dstlen + 1 < dstsize && src[i])
		dst[dstlen++] = src[i++];
	if (dstsize != 0 || ogdst < dstsize)
		dst[dstlen] = '\0';
	return (ans);
}
