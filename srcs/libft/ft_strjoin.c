/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:35:12 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/05/22 20:05:15 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ns;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ns = ft_calloc(s1_len + s2_len + 1, sizeof(char));
	i = 0;
	j = 0;
	if (!ns)
		return (NULL);
	while (i < s1_len)
		ns[j++] = s1[i++];
	i = 0;
	while (i < s2_len)
		ns[j++] = s2[i++];
	ns[j] = '\0';
	return (ns);
}
