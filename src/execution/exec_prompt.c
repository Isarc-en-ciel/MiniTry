/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/06 14:49:34 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_builtin	*find_builtin(t_shell *sh, t_command *cmd)
{
	int			i;
	t_builtin	*builtin;
	char		*cmd_name;

	i = 0;
	builtin = &sh->builtin_cmds[i];
	cmd_name = cmd->cmd[0];
	while (i != 7)
	{
		builtin = &sh->builtin_cmds[i];
		if (!ft_strncmp(builtin->name, cmd_name, ft_strlen(builtin->name)))
		{
			return (builtin);
		}
		i++;
	}
	return (NULL);
}

static	t_shell	*clean_prompt(t_shell *shell)
{
	free_tab_cmd(shell->tab_size, shell->tab);
	shell->tab_size = 0;
	shell->tab = NULL;
	if (shell->child_pid)
	{
		free(shell->child_pid);
		shell->child_pid = NULL;
	}
	return (shell);
}

int	exec_prompt(t_shell *shell)
{
	exec_pipeline(shell);
	shell = clean_prompt(shell);
	ft_printf("exit status : %d\n", shell->exit_status);
	return (shell->exit_status);
}
