/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:21:03 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/10 16:11:16 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//The return status is zero unless a name is readonly or may not be unset. 

void	remove_env(t_env_list **head, char *key)
{
	t_env_list	*ptr;
	t_env_list	*second_elem;
	t_env_list	*prev;

	second_elem = (*head)->next;
	ptr = get_env(key, *head);
	if (!ptr)
		return ;
	if (!ft_strncmp((*head)->key, key, ft_strlen(key))
			&& !(ft_strncmp((*head)->key, key, ft_strlen((*head)->key))))
	{
		delete_env(*head);
		(*head) = second_elem;
		return ;
	}
	prev = get_prev_env(head, key);
	if (!prev)
		return ;
	prev->next = prev->next->next;
	delete_env(ptr);
}

int	ft_unset(char ***envp, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	int			i;

	head = array_to_list(*envp);
	exit_status = SUCCESS;
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	i = 1;
	while (cmd->cmd[i])
	{
		if (!is_key_format(cmd, cmd->cmd[i]))
		{
			exit_status = FAIL;
		}
		remove_env(&head, cmd->cmd[i]);
		i++;
	}
	build_envp(&head, cmd, envp);
	destroy_lst(&head);
	if (cmd->error.code != OK)
		exit_status = FAIL;
	return (exit_status);
}
