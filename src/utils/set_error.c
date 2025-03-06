/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:14:27 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/06 15:46:22 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_error	set_error(char *str, enum e_error code)
{
	t_error	new_error;

	new_error.str_perror = str;
	new_error.code = code;
	if (str)
		perror(str);
	return (new_error);
}
