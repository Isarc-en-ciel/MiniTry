/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:11:33 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/11 15:19:16 by csteylae         ###   ########.fr       */
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
		ft_printf("cannot list to array :(\n");
		builtin_error(cmd, "malloc", MALLOC, head);
		return ;
	}
	free_tab_char(*envp);
	*envp = new_envp;
}

bool is_key_format(t_command *cmd, char *str)
{
	if (str[0] != '_' && !ft_isalpha(str[0])) 
	{
		ft_printf("%s : '%s': not a valid identifier\n", cmd->cmd[0], str);
		return (false);
	}
	return (true);
}



//void	ft_print_list(t_env_list *head)
//{
//	t_env_list	*tmp;
//	tmp = head;
//	while (tmp)
//	{
//		if (tmp->value)
//			ft_printf("%s=%s\n", tmp->key, tmp->value);
//		tmp = tmp->next;
//	}
//}
