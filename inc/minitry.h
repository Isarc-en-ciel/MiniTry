/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:20:28 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/18 14:53:36 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITRY_H

#define MINITRY_H

#include "minitry_lib.h"
#include "minitry_struct.h"
#include "minitry_function.h"

# define READ_FROM 0
# define WRITE_TO 1

t_lexer	create_pipe(char *input, int *position, t_lexer token);
t_lexer	create_redirect_in(char *input, int *position, t_lexer token);
t_lexer	create_redirect_out(char *input, int *position, t_lexer token);
t_lexer	create_doubleq(char *input, int *position, t_lexer token);
t_lexer	create_simpleq(char *input, int *position, t_lexer token);
t_lexer	create_word(char *input, int *position, t_lexer token);
int	    check_open_quotes(char *str, char c, int j);
void	*ft_memcpy_plus(void *dst, const void *src, int start, int n);

#endif
