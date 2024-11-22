/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:59:48 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/22 12:08:21 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char ***envp, t_command *cmd)
{
	t_env_list	*head;
	int			i;

	head = NULL;
	if (!envp || !*envp)
		return (0);
	if (cmd->cmd[1])
		return (builtin_error(cmd, cmd->cmd[0], BUILTIN_ARG, &head));
	i = 0;
	head = array_to_list(*envp);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, &head));
	replace_env("_", "usr/bin/env", &head, cmd);
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, cmd->error.code, &head));
	build_envp(&head, cmd, envp);
	if (cmd->error.code != OK)
		return (-1);
	ft_print_list(head);
	destroy_lst(&head);
	return (0);
}
