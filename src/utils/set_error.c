/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:14:27 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/14 18:32:46 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_error	set_error(char *str, enum e_error code)
{
	t_error	new_error;

	new_error.str_perror = str;
	new_error.code = code;
	if (code == FILE_NO_EXIST)
	{
		ft_putstr_fd(str , 1);
		ft_putstr_fd(" : No such file or directory\n", 1);
	}
	else if (code == FILE_NO_PERM)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : Permission denied\n", 1);
	}
	return (new_error);
}
