/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:01:23 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 14:10:38 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned int	i;

	ptr = NULL;
	i = 0;
	while ((unsigned char)s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			ptr = (unsigned char *)&s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		ptr = (unsigned char *)&s[i];
	return ((char *)ptr);
}
