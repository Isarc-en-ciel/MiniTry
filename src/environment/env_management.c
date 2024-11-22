/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:06:28 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/22 18:12:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	env_error(t_command *cmd, char *str, enum e_error code)
{
	cmd->error = set_error(str, code);
	return ;
}

t_env_list	*find_prev_env(t_env_list **head, char *key)
{
	t_env_list	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
		{
			if (!ft_strncmp(tmp->next->key, key, ft_strlen(tmp->next->key)))
				break;
		}
		tmp = tmp->next;
	}
	return (tmp);
}

void	replace_env(char *key, char *value, t_env_list **head, t_command *cmd)
{
	t_env_list	*tmp;
	t_env_list	*new;

	new = new_env_list(key, value);
	if (!new)
		return (env_error(cmd, "malloc", MALLOC));
	tmp = find_prev_env(head, key);
	if (!tmp)
		return ;
	new->next = tmp->next->next;
	delete_env(tmp->next);
	tmp->next = new;
}

t_env_list	*get_env(char *key, t_env_list *head)
{
	t_env_list	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(tmp->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
