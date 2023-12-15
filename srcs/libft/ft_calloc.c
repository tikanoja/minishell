/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:49:07 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 16:54:25 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	if (count != 0 && size != 0)
	{
		if ((count * size) / size != count)
			return (NULL);
	}
	ptr = (void *)malloc(size * count);
	if (ptr == NULL)
		return (ptr);
	else
		ft_bzero(ptr, (size * count));
	return ((void *)ptr);
}
