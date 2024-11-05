/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:36:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/05 17:35:26 by iwaslet          ###   ########.fr       */
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
	tmp->value = ft_strdup(new_value);
	if (!tmp->value)
		return (NULL);
	return (tmp);
}
