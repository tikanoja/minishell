/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:04:55 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/12/09 17:28:20 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_ret(char c)
{
	write (1, &c, 1);
	return (1);
}

int	ft_putstr_ret(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		str = "(null)";
	while (str[i])
	{
		ft_putchar_ret(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr_ret(int n)
{
	int	sign;

	sign = 0;
	if (n == -2147483648)
	{
		ft_putstr_ret("-2147483648");
		return (11);
	}
	if (n < 0)
	{
		ft_putchar_ret('-');
		n = n * -1;
		sign = 1;
	}
	if (n > 9)
	{
		ft_putnbr_ret(n / 10);
	}
	ft_putchar_ret((n % 10) + 48);
	return (intlen(n) + sign);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		ret;
	va_list	args;

	i = 0;
	ret = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ret = ret - 2 + formats1(&str[i], args);
			if (str[i] != '\0')
				i++;
		}
		if (str[i] == '\0')
			break ;
		if (str[i] == '%')
			continue ;
		ft_putchar_ret(str[i]);
		i++;
	}
	va_end(args);
	return (i + ret);
}
