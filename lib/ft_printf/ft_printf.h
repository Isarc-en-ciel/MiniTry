/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:23:45 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/17 13:34:17 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putnbr_base(long nb, int len, char *base);
int		ft_putnbr_unsigned(unsigned long nb, unsigned long len, char *base);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_printf(const char *str, ...);
typedef struct ft_printf_data
{
	int	current;
	int	old;
}	t_ft_printf_data;

#endif
