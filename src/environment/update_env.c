/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:52 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 15:29:50 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	create_env(t_env_list **head, char *key, char *val)
{
	t_env_list	*elem;

	elem = new_env_list(key, val, true);
	if (!elem)
	{
		perror("malloc");
		return (false);
	}
	lst_addback(head, elem);
	return (true);
}

static t_env_list	*replace_env_value(t_env_list *elem, char *new_value)
{
	if (!elem)
		return (NULL);
	if (elem->value)
	{
		free(elem->value);
		elem->value = NULL;
	}
	if (!new_value)
		elem->value = NULL;
	else
	{
		elem->value = ft_strdup(new_value);
		if (!elem->value)
		{
			perror("malloc");
			return (NULL);
		}
	}
	return (elem);
}

bool	update_env(t_env_list **head, char *key, char *value)
{
	t_env_list	*elem;

	elem = get_env(key, head);
	if (!elem)
	{
		if (!create_env(head, key, value))
			return (false);
	}
	else
	{
		if (!replace_env_value(elem, value))
			return (false);
	}
	return (true);
}
