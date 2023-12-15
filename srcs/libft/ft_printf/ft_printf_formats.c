/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formats.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:26:47 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/12/10 12:28:50 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	formats2(const char *str, va_list args, int i)
{
	if (*str == 'x')
		i = ft_puthexalow(va_arg(args, unsigned int));
	else if (*str == 'X')
		i = ft_puthexaup(va_arg(args, unsigned int));
	else if (*str == 'p')
	{
		ft_putstr_ret("0x");
		i = 2 + ft_putptr(va_arg(args, size_t));
	}
	else if (*str == '%')
		i = i + ft_putchar_ret('%');
	else if (*str == '\0')
		i = 1;
	return (i);
}

int	formats1(const char *str, va_list args)
{
	int	i;

	i = 0;
	if (*str == 'c')
		i = ft_putchar_ret(va_arg(args, int));
	else if (*str == 's')
		i = ft_putstr_ret(va_arg(args, char *));
	else if (*str == 'd')
		i = ft_putnbr_ret(va_arg(args, int));
	else if (*str == 'i')
		i = ft_putnbr_ret(va_arg(args, int));
	else if (*str == 'u')
		i = ft_putunsigned(va_arg(args, unsigned int));
	else
		i = formats2(str, args, i);
	return (i);
}
