/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:52 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/03 14:54:28 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_new_env(t_env_list **head, char *key, char *value, t_command *cmd)
{
	t_env_list	*elem;

	elem = new_env_list(key, value);
	if (!elem)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	lst_addback(head, elem);
}

void	update_env(t_command *cmd, t_env_list **head, char *key, char *value)
{
	t_env_list	*elem;

	elem = get_env(key, *head);
	if (!elem)
		create_new_env(head, key, value, cmd);
	else
		replace_env(key, value, head, cmd);
}

t_env_list	*get_prev_env(t_env_list **head, char *key)
{
	t_env_list	*tmp;
	
	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
		{
			if (!ft_strncmp(tmp->next->key, key, ft_strlen(tmp->next->key)) 
				&& ! ft_strncmp(tmp->next->key, key, ft_strlen(key)))
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
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	tmp = get_prev_env(head, key);
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
		if (!ft_strncmp(key, tmp->key, ft_strlen(key)) 
				&& !ft_strncmp(key, tmp->key, ft_strlen(tmp->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}
