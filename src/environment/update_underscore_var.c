/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_underscore_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:52:18 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 15:17:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	update_underscore_var(t_shell *sh)
{
	t_command	*last_cmd;
	t_env_list	*head;

	last_cmd = &sh->tab[sh->tab_size - 1];
	head = array_to_list(sh->env);
	if (!head)
	{
		last_cmd->error = set_error("malloc", MALLOC);
		sh->exit_status = 1;
		return ;
	}
	update_env(&head, "_", last_cmd->cmd[0]);
	build_envp(&head, last_cmd, &sh->env);
	destroy_lst(&head);
}
