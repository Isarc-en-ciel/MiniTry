/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:24:42 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/17 13:34:33 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_format(va_list *arg, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_putnbr_base(va_arg(*arg, int), 10, "0123456789"));
	else if (c == 'X')
		return (ft_putnbr_base((unsigned int)va_arg(*arg, int),
				16, "0123456789ABCDEF"));
	else if (c == 'x')
		return (ft_putnbr_base((unsigned int)va_arg(*arg, int),
				16, "0123456789abcdef"));
	else if (c == 'u')
		return (ft_putnbr_unsigned((unsigned int)va_arg(*arg, unsigned int),
				10, "0123456789"));
	else if (c == 'p')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		return (2 + ft_putnbr_unsigned((unsigned long)va_arg(*arg, void *),
				16, "0123456789abcdef"));
	}
	else if (c == 'c')
		return (ft_putchar((char)va_arg(*arg, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*arg, char *)));
	else if (c == '%')
		return (ft_putchar(c));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list					arg;
	struct ft_printf_data	check;

	check.current = 0;
	va_start(arg, str);
	while (*str != '\0' && str)
	{
		if (*str == '%')
		{
			str++;
			check.old = check.current;
			check.current = check.current + check_format(&arg, *str);
			if (check.current < check.old)
				return (-1);
		}
		else if (*str != '\0')
		{
			if (ft_putchar(*str) == -1)
				return (-1);
			check.current++;
		}
		str++;
	}
	va_end (arg);
	return (check.current);
}
