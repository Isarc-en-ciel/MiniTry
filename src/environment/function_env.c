/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:41:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 17:21:03 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*new_env_list(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new->value);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	lst_addback(t_env_list **head, t_env_list *new)
{
	t_env_list	*tmp;

	if (!head || !new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	delete_env(t_env_list *elem)
{
	if (elem->value)
		free(elem->value);
	if (elem->key)
		free(elem->key);
	free(elem);
}

int		get_list_size(t_env_list *head)
{
	int			i;
	t_env_list	*tmp;

	i = 0;
	tmp = head;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	destroy_lst(t_env_list **head)
{
	t_env_list *tmp;

	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		*head = tmp;
	}
}