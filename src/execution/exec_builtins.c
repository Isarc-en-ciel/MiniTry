/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:21 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 11:57:59 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_builtin	*find_builtin(t_shell *sh, t_command *cmd)
{
	int			i;
	t_builtin	*builtin;
	char		*cmd_name;

	i = 0;
	builtin = &sh->builtin[i];
	cmd_name = cmd->cmd[0];
	while (i != 7)
	{
		builtin = &sh->builtin[i];
		if (key_found((char *)builtin->name, cmd_name))
			return (builtin);
		i++;
	}
	return (NULL);
}

void	exec_builtin(t_builtin *builtin, t_command *cmd, t_shell *sh)
{
	if (builtin && sh->tab_size == 1)
	{
		perform_redirection(sh, &sh->tab[0]);
		if (sh->tab[0].error.code != SUCCESS)
		{
			sh->exit_status = sh->tab[0].error.code;
			return ;
		}
	}
	sh->exit_status = builtin->func(sh, cmd);
}
