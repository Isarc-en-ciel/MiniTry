/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:14:27 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/08 16:21:32 by csteylae         ###   ########.fr       */
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
	/*
	if (code == CMD_NOT_FOUND)
	{
		new_error.code = FILE_NO_EXIST;
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : Command not found\n", 1);
		return (new_error);
	}
	else if (code == FILE_NO_EXIST)
	{
		ft_putstr_fd(str , 1);
		ft_putstr_fd(" : No such file or directory\n", 1);
		return (new_error);
	}
	else if (code == FILE_NO_PERM)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : Permission denied\n", 1);
		return (new_error);
	}
	else if (code == BUILTIN_OPT)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : no option allowed\n", 1);
		return (new_error);
	}
	*/
	//else if (code != CD_ERROR) 
	//if (code != CD_ERROR) 
	//	perror(str);
//	return (new_error);
}
/*
t_error	set_error(char *str, enum e_error code)
{
	t_error	new_error;

	new_error.str_perror = str;
	new_error.code = code;
	if (code == CMD_NOT_FOUND)
	{
		new_error.code = FILE_NO_EXIST;
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : Command not found\n", 1);
		return (new_error);
	}
	else if (code == FILE_NO_EXIST)
	{
		ft_putstr_fd(str , 1);
		ft_putstr_fd(" : No such file or directory\n", 1);
		return (new_error);
	}
	else if (code == FILE_NO_PERM)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : Permission denied\n", 1);
		return (new_error);
	}
	else if (code == BUILTIN_OPT)
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd(" : no option allowed\n", 1);
		return (new_error);
	}
	else if (code != CD_ERROR) 
		perror(str);
	return (new_error);
}
*/
