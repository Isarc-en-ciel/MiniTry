/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:21:03 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/06 15:16:08 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//The return status is zero unless a name is readonly or may not be unset. 

void	remove_env(t_env_list **head, char *key)
{
	t_env_list	*ptr;
	t_env_list	*prev;

	ptr = get_env(key, *head);
	if (!ptr)
	{
		ft_printf("env var not found \n");
		return ;
	}
	prev = get_prev_env(head, key);
	if (!prev)
		return ;
	prev->next = prev->next->next;
	delete_env(ptr);
}

bool is_key_format(char *str)
{
	if (str[0] != '_' || !ft_isalpha(str[0])) //must modify this
		return (false);
	return (true);
}

int	ft_unset(char ***envp, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	int			status;
	int			i;

	(void)exit_status;
	head = array_to_list(*envp);
	status = SUCCESS;
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	i = 1;
	while (cmd->cmd[i])
	{
		if (!is_key_format(cmd->cmd[i]))
			status = FAIL;
		remove_env(&head, cmd->cmd[i]);
		i++;
	}
	build_envp(&head, cmd, envp);
	destroy_lst(&head);
	if (cmd->error.code != SUCCESS)
		status = FAIL;
	return (status);
}
