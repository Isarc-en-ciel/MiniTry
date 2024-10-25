/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:36:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/25 19:00:11 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_env_list	*new_env_list(char *key, char *value)
{
	t_env_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->value = value;
	new->key = key;
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

t_env_list	*find_node(char *key, t_env_list *head)
{
	t_env_list	*tmp;

	if (!head)
		return (NULL);
	tmp = head;
	while(tmp)
	{
		if (!ft_strncmp(key, tmp->key, ft_strlen(tmp->key)))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
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
