/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:23 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/07 13:19:24 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_shell *sh, t_command *cmd)
{
	char		*str;

	str = NULL;
	(void)sh;
	if (cmd->cmd[1])
		return (builtin_error(cmd, cmd->cmd[0], FAIL, NULL));
	str = getcwd(NULL, 0);
	if (!str)
		return (builtin_error(cmd, "getcwd", SYSCALL_ERROR, NULL));
	ft_printf("%s\n", str);
	free(str);
	return (0);
}
