/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:23 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/05 11:48:59 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* pwd is just a simple syscall getcwd */

int	ft_pwd(char ***env, t_command *cmd, int exit_status)
{
	char		*str;

	(void)env;
	(void) exit_status;
	str = NULL;
	if (cmd->cmd[1])
		return  (builtin_error(cmd, cmd->cmd[0], BUILTIN_OPT, NULL));
	str = getcwd(NULL, 0);
	if (!str)
	{
		return (builtin_error(cmd, "getcwd", SYSCALL_ERROR, NULL));
	}
	ft_printf("%s\n", str);
	free(str);
	return (0);
}
