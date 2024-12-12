/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:41:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/12 12:39:39 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*new_env_list(char *key, char *value, bool is_init)
{
	t_env_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
	{
		delete_env(new);
		return (NULL);
	}
	if (!value)
	{
		ft_printf("oh this is null\n");
		new->value = NULL;
	}
	else if (value[0] == '\0')
	{
		new->value = ft_calloc(1, sizeof(char));
		if (!new->value)
		{
			delete_env(new);
			return (NULL);
		}
	}
	else
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			delete_env(new);
			return (NULL);
		}
	}
	new->is_init = is_init;
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
	elem = NULL;
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
	while (*head)
	{
		tmp = (*head)->next;
		delete_env(*head);
		*head = tmp;
	}
}
