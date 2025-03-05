/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:21:03 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/05 19:11:19 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_env(t_env_list **head, char *key)
{
	t_env_list	*ptr;
	t_env_list	*second_elem;
	t_env_list	*prev;

	second_elem = (*head)->next;
	ptr = get_env(key, head);
	if (!ptr)
		return ;
	if (key_found((*head)->key, key))
	{
		delete_env(*head);
		if (second_elem)
			(*head) = second_elem;
		else
			*head = NULL;
		return ;
	}
	prev = get_prev_env(head, key);
	if (!prev)
		return ;
	prev->next = prev->next->next;
	delete_env(ptr);
}

int	ft_unset(t_shell *sh, t_command *cmd)
{
	t_env_list	*head;
	int			i;

	head = array_to_list(sh->env);
	sh->exit_status = SUCCESS;
	if (sh->env && !head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	i = 1;
	if (!head)
		return (sh->exit_status);
	while (cmd->cmd[i])
	{
		remove_env(&head, cmd->cmd[i]);
		i++;
	}
	build_envp(&head, cmd, &sh->env);
	destroy_lst(&head);
	if (cmd->error.code != SUCCESS)
		sh->exit_status = FAIL;
	return (sh->exit_status);
}
