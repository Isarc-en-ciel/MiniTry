/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:59:48 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/22 18:29:16 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//void	init_empty_env();
//this function must must be called at the level of the initiation, before the while (1) in main function


int	ft_env(char ***envp, t_command *cmd)
{
	t_env_list	*head;
	int			i;

	head = NULL;
	i = 0;
	if (cmd->cmd[1])
		return (builtin_error(cmd, cmd->cmd[0], BUILTIN_OPT, &head));
	if (*envp)
	{
		head = array_to_list(*envp);
		if (!head)
			return (builtin_error(cmd, "malloc", MALLOC, &head));
	}
	update_env(cmd, &head, "_", "usr/bin/env");
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, cmd->error.code, &head));
	build_envp(&head, cmd, envp);
	if (cmd->error.code != OK)
		return (1);
	ft_print_list(head);
	destroy_lst(&head);
	return (0);
}
