/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:14:27 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/07 12:23:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_error	set_error(char *str, enum e_error code)
{
	t_error	new_error;

	new_error.str_perror = str;
	new_error.code = code; 
	if (code == CMD_NOT_FOUND)
	{
		ft_printf("%s: command not found\n", str);
	}
	else if (str)
		perror(str);
	return (new_error);
}
