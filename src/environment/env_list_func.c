/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:36:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/29 16:54:09 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

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

t_env_list	*env_modify_value(char *key, char *new_value, t_env_list **head)
{
	t_env_list	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = find_node(key, *head);
	if (!tmp)
		return (NULL);
	if (tmp->value)
		free(tmp->value);
	tmp->value = new_value;
	return (tmp);
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
