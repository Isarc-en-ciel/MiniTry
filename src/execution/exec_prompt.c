/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/03 16:46:31 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell	*clean_prompt(t_shell *shell)
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

bool	is_error_with_cmd(t_command *cmd)
{
	if (!cmd
		|| cmd->error.code != SUCCESS
		|| !cmd->cmd
		|| !cmd->cmd[0]
		|| cmd->cmd[0][0] == '\0')
	{
		return (true);
	}
	return (false);
}

static void	perform_cmd_redirection(t_shell *sh)
{
	int	i;

	i = 0;
	while (i != sh->tab_size)
	{
		perform_redirection(sh, &sh->tab[i]);
		i++;
	}
}

void	exec_prompt(t_shell *sh)
{
	struct sigaction	interactive_sigint;
	struct sigaction	interactive_sigquit;
	t_builtin			*builtin;

	sigaction(SIGINT, NULL, &interactive_sigint);
	sigaction(SIGQUIT, NULL, &interactive_sigquit);
	set_signal_in_parent(sh);
	perform_cmd_redirection(sh);	
	builtin = find_builtin(sh, &sh->tab[0]);
	if (builtin && sh->tab_size == 1)
		exec_builtin(builtin, &sh->tab[0], sh);
	else
	{
		init_child_pid(sh);
		exec_pipeline(sh);
	}
	sigaction(SIGINT, &interactive_sigint, NULL);
	sigaction(SIGQUIT, &interactive_sigquit, NULL);
	sh = clean_prompt(sh);
}
