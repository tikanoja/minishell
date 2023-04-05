/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:29:20 by ttikanoj          #+#    #+#             */
/*   Updated: 2022/12/13 10:51:26 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_putunsigned(unsigned int n);
int	formats1(const char *str, va_list args);
int	formats2(const char *str, va_list args, int i);
int	ft_putnbr_ret(int n);
int	ft_putstr_ret(char *str);
int	ft_putchar_ret(char c);
int	ft_puthexalow(unsigned int n);
int	ft_puthexaup(unsigned int n);
int	ft_putptr(size_t ptr);
int	intlen(int num);

#endif
