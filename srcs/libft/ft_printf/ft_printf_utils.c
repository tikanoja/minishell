/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 17:12:01 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/12/09 17:28:49 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intlen(int num)
{
	int	i;

	i = 1;
	while (num > 9)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int	ft_putunsigned(unsigned int n)
{
	int				ret;
	unsigned int	cpy;

	cpy = n;
	ret = 1;
	while (cpy > 9)
	{
		cpy = cpy / 10;
		ret++;
	}
	if (n < 0)
	{
		ft_putchar_ret('-');
		n = n * -1;
	}
	if (n > 9)
		ft_putunsigned(n / 10);
	ft_putchar_ret((n % 10) + 48);
	return (ret);
}

int	ft_puthexalow(unsigned int n)
{
	int				ret;
	unsigned int	cpy;

	cpy = n;
	ret = 1;
	while (cpy > 15)
	{
		cpy = cpy / 16;
		ret++;
	}
	if (n > 15)
		ft_puthexalow(n / 16);
	n = n % 16;
	if (n <= 15 && n > 9)
		ft_putchar_ret(n + 87);
	if (n < 10)
		ft_putchar_ret(n + 48);
	return (ret);
}

int	ft_puthexaup(unsigned int n)
{
	int				ret;
	unsigned int	cpy;

	cpy = n;
	ret = 1;
	while (cpy > 15)
	{
		cpy = cpy / 16;
		ret++;
	}
	if (n > 15)
		ft_puthexaup(n / 16);
	n = n % 16;
	if (n <= 15 && n > 9)
		ft_putchar_ret(n + 55);
	if (n < 10)
		ft_putchar_ret(n + 48);
	return (ret);
}

int	ft_putptr(size_t ptr)
{
	int		ret;
	size_t	cpy;
	size_t	n;

	ret = 1;
	cpy = ptr;
	n = ptr;
	while (cpy > 15)
	{
		cpy = cpy / 16;
		ret++;
	}
	if (n > 15)
		ft_putptr(n / 16);
	n = n % 16;
	if (n <= 15 && n > 9)
		ft_putchar_ret(n + 87);
	if (n < 10)
		ft_putchar_ret(n + 48);
	return (ret);
}
