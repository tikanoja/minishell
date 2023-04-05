/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:05:54 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/11/16 16:18:59 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(long num)
{
	int	len;

	len = 1;
	while (num > 9)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

static char	*assignpos(char *str, int len, long num)
{
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = num % 10 + 48;
		num = num / 10;
		len--;
	}
	return (str);
}

static char	*assignneg(char *str, int len, long num)
{
	len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	str[0] = '-';
	len--;
	while (len >= 1)
	{
		str[len] = num % 10 + 48;
		num = num / 10;
		len--;
	}
	return (str);
}

static char	*minint(char *str, long num)
{
	char	*min;
	int		i;

	i = 0;
	min = "-2147483648";
	if (num == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * 11 + 1);
	if (str == NULL)
		return (NULL);
	while (i < 12)
	{
		str[i] = min[i];
		i++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	size_t	len;
	long	num;

	num = n;
	sign = 1;
	str = 0;
	if (num == -2147483648 || num == 0)
		return (minint(str, num));
	if (num < 0)
	{
		num *= -1;
		sign *= -1;
	}
	len = getlen(num);
	if (sign == -1)
		str = assignneg(str, len, num);
	else
		str = assignpos(str, len, num);
	return (str);
}
