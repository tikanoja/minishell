/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:35:12 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/05/16 14:05:53 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
        int             sum;
        char    *ns;
        int             i;
        int             j;

        sum = ft_strlen(s1) + ft_strlen(s2);
        if (s1 == NULL || s2 == NULL)
                return (NULL);
		ns = ft_calloc(sum + 1, sizeof(char));
        if (!ns)
                return (NULL);
        i = 0;
        j = 0;
        while ((size_t)i < ft_strlen(s1))
                ns[j++] = s1[i++];
        i = 0;
        while ((size_t)i < ft_strlen(s2))
                ns[j++] = s2[i++];
        ns[j] = '\0';
        return (ns);
}
