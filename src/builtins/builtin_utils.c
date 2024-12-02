/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:11:33 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/02 14:28:44 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin_error(t_command *cmd, char *str, enum e_error code, t_env_list **head)
{
	if (cmd->error.code == OK)
		cmd->error = set_error(str, code);
	if (head && *head)
		destroy_lst(head);
	return (FAIL);
}

void	build_envp(t_env_list **head, t_command *cmd, char ***envp)
{
	char **new_envp;

	new_envp = list_to_array(head);
	if (!new_envp)
	{
		builtin_error(cmd, "malloc", MALLOC, head);
		return ;
	}
	free_tab_char(*envp);
	*envp = new_envp;
}

//void	ft_print_list(t_env_list *head)
//{
//	t_env_list	*tmp;
//
//	tmp = head;
//	while (tmp)
//	{
//		if (tmp->value)
//			ft_printf("%s=%s\n", tmp->key, tmp->value);
//		tmp = tmp->next;
//	}
//}
