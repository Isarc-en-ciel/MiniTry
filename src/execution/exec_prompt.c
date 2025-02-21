/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 12:09:50 by csteylae         ###   ########.fr       */
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

/*
static bool is_only_redirection(t_shell *sh)
{
	if (sh->tab_size > 1)
		return (false);
	if (!sh->tab[0].cmd && sh->tab[0].redirection.size > 0)
	{
		perform_redirection(sh, &sh->tab[0]);
		return (true);
	}
	return (false);
}
*/

void	exec_prompt(t_shell *sh)
{
	struct sigaction	old_act;
	t_builtin			*builtin;

	sigaction(SIGINT, NULL, &old_act);
	sh->signal_act = setup_signal_in_parent();
	builtin = find_builtin(sh, &sh->tab[0]);
	if (builtin && sh->tab_size == 1)
		exec_builtin(builtin, &sh->tab[0], sh);
	else
	{
		init_child_pid(sh);
		exec_pipeline(sh);
	}
	sigaction(SIGINT, &old_act, NULL);
	sh = clean_prompt(sh);
}
