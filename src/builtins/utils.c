/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:03:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 17:04:07 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_error(t_command *cmd, char *str, enum e_error code, t_env_list **head)
{
	cmd->error = set_error(str, code);
	if (head && *head)
		destroy_lst(head);
	return (-1);
}

void	build_envp(t_env_list **head, t_command *cmd, char **envp)
{
	char **new_envp;

	new_envp = list_to_array(head);
	if (!new_envp)
	{
		builtin_error(cmd, "malloc", MALLOC, head);
		return ;
	}
	free_tab_char(envp);
	envp = new_envp;
	destroy_lst(head);
	return ;
}
