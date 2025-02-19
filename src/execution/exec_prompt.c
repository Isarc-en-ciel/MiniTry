/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/19 15:04:04 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	exec_prompt(t_shell *shell)
{
	if (is_only_redirection(shell))
		return (shell->exit_status);
	if (is_only_one_builtin(shell, 0))
	{
		ft_printf("builtin return : %i\n", shell->exit_status);
		return (shell->exit_status);
	}
	exec_pipeline(shell);
	shell = clean_prompt(shell);
	ft_printf("exit status : %d\n", shell->exit_status);
	return (shell->exit_status);
}
