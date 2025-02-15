/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/11 15:24:07 by csteylae         ###   ########.fr       */
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

int	exec_prompt(t_shell *shell)
{
	if (is_only_one_builtin(shell, 0))
		return (shell->exit_status);
	exec_pipeline(shell);
	shell = clean_prompt(shell);
	ft_printf("exit status : %d\n", shell->exit_status);
	return (shell->exit_status);
}
