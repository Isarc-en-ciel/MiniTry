/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:52 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/11 17:08:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	create_new_env(t_env_list **head, char *key, char *value, t_command *cmd)
{
	t_env_list	*elem;

	elem = new_env_list(key, value, true);
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
		if (new_value[0] == '\0')
		{
			elem->value = ft_calloc(1, sizeof(char));
			if (!elem->value)
			{
				cmd->error = set_error("malloc", MALLOC);
				return ;
			}
		}
		else
		{
			elem->value = ft_strdup(new_value);
			if (!elem->value)
				cmd->error = set_error("malloc", MALLOC);
		}
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
		create_new_env(head, key, value, cmd);
		return ;
	}
	else
	{
		replace_env_value(elem, value, cmd);
	}
}


//void	create_new_env(t_env_list **head, char *key, char *value, t_command *cmd)
//{
//	t_env_list	*elem;
//
//	elem = new_env_list(key, value, true);
//	if (!elem)
//	{
//		cmd->error = set_error("malloc", MALLOC);
//		return ;
//	}
//	lst_addback(head, elem);
//}
//
//void	update_env(t_command *cmd, t_env_list **head, char *key, char *value)
//{
//	t_env_list	*elem;
//
//	elem = get_env(key, *head);
//	if (!elem)
//	{
//		create_new_env(head, key, value, cmd);
//	}
//	else
//		replace_env(key, value, head, cmd);
//}
//
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
//
//void	replace_env(char *key, char *value, t_env_list **head, t_command *cmd)
//{
//	t_env_list	*tmp;
//	t_env_list	*new;
//
//	new = new_env_list(key, value, true);
//	tmp = *head;
//	if (!new)
//	{
//		cmd->error = set_error("malloc", MALLOC);
//		return ;
//	}
//	if (!ft_strncmp(key, (*head)->key, ft_strlen(key)
//			&& !ft_strncmp(key, (*head)->key, ft_strlen((*head)->key))))
//	{
//		ft_printf("key : %s, head->key : %s, ft_strlen(key) %d ft_strlen(head->key) %i\n",
//			   	key, (*head)->key, ft_strlen(key), ft_strlen((*head)->key));
////		ft_printf("the elem to replace is the head's list\n");
//		new->next = (*head)->next;
//		delete_env(*head);
//		*head = new;
//		return ;
//	}
//	tmp = get_prev_env(head, key);
//	if (!tmp)
//	{
//		ft_printf("not found\n");
//		return ;
//	}
//	new->next = tmp->next->next;
//	delete_env(tmp->next);
//	tmp->next = new;
//}
//
//t_env_list	*get_env(char *key, t_env_list *head)
//{
//	t_env_list	*tmp;
//
//	if (!head || !key)
//		return (NULL);
//	tmp = head;
//	while (tmp)
//	{
//		if (key_found(key, tmp->key))
//			break ;
//		tmp = tmp->next;
//	}
//	return (tmp);
//}
