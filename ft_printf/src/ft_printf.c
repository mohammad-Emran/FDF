/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:47:37 by malja-fa          #+#    #+#             */
/*   Updated: 2024/11/24 14:14:46 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_hex(unsigned long value, int uppercase)
{
	char	*base;
	int		i;

	i = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (value >= 16)
		i += ft_print_hex(value / 16, uppercase);
	i += ft_putchar(base[value % 16]);
	return (i);
}

int	ft_putp(void *p)
{
	int				i;
	unsigned long	s;

	s = (unsigned long)(p);
	i = 0;
	if (s == 0)
		return (ft_putstr("(nil)"));
	i += ft_putstr("0x");
	i += ft_print_hex(s, 0);
	return (i);
}

int	ft_chose(char *format, va_list	args)
{
	if (*format == 'd' || *format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (*format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*format == '%')
		return (ft_putchar('%'));
	else if (*format == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), 0));
	else if (*format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), 1));
	else if (*format == 'u')
		return (ft_putunbr(va_arg(args, unsigned int)));
	else if (*format == 'p')
		return (ft_putp(va_arg(args, void *)));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;

	counter = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			counter += ft_chose((char *)format, args);
		}
		else
			counter += ft_putchar(*format);
		format++;
	}
	va_end(args);
	return (counter);
}
/*
int	main ()
{
	ft_printf(" %i %i %s %x %X\n", 0, 0, "kjhkhkj", 111, 111);
}
*/
