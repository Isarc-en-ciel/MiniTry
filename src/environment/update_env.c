/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:52 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/13 19:56:28 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	create_env(t_env_list **head, char *key, char *val, t_command *cmd)
{
	t_env_list	*elem;

	elem = new_env_list(key, val, true);
	if (!elem)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	lst_addback(head, elem);
}

static void	replace_env_value(t_env_list *elem, char *new_value, t_command *cmd)
{
	if (!elem)
		return ;
	if (elem->value)
		free(elem->value);
	if (!new_value)
		elem->value = NULL;
	else
	{
		elem->value = ft_strdup(new_value);
		if (!elem->value)
			cmd->error = set_error("malloc", MALLOC);
	}
}

t_env_list	*get_env(char *key, t_env_list **head)
{
	t_env_list	*tmp;

	if (!head || !*head || !key)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if (key_found(key, tmp->key))
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	update_env(t_command *cmd, t_env_list **head, char *key, char *value)
{
	t_env_list	*elem;

	elem = get_env(key, head);
	if (!elem)
	{
		create_env(head, key, value, cmd);
		return ;
	}
	else
	{
		replace_env_value(elem, value, cmd);
	}
}

t_env_list	*get_prev_env(t_env_list **head, char *key)
{
	t_env_list	*tmp;

	if (!head || !*head || !key)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
		{
			if (key_found(tmp->next->key, key))
				break ;
		}
		tmp = tmp->next;
	}
	return (tmp);
}
