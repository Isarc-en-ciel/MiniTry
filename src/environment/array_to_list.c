/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:26:54 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 13:29:14 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**split_key_from_value(char *str)
{
	char	**tab_key_value;

	tab_key_value = NULL;
	if (!str)
		return (NULL);
	tab_key_value = ft_split(str, '=');
	if (!tab_key_value)
		return (NULL);
	return (tab_key_value);
}

static t_env_list	*create_node_with_value(char *str)
{
	t_env_list	*new;
	char		**pair_key_value;

	new = NULL;
	pair_key_value = split_key_from_value(str);
	if (!pair_key_value)
		return (NULL);
	if (!pair_key_value[1])
		new = new_env_list(pair_key_value[0], "", true);
	else
		new = new_env_list(pair_key_value[0], pair_key_value[1], true);
	free_tab_char(pair_key_value);
	if (!new)
		return (NULL);
	return (new);
}

static t_env_list	*get_new_node(char *str)
{
	t_env_list	*new;

	new = NULL;
	if (!ft_strchr(str, '='))
	{
		new = new_env_list(str, NULL, false);
		if (!new)
			return (NULL);
	}
	else
	{
		new = create_node_with_value(str);
		if (!new)
			return (NULL);
	}
	return (new);
}

t_env_list	*array_to_list(char **env)
{
	t_env_list	*head;
	t_env_list	*new;
	int			i;

	head = NULL;
	new = NULL;
	i = 0;
	while (env[i])
	{
		new = get_new_node(env[i]);
		if (!new)
		{
			destroy_lst(&head);
			return (NULL);
		}
		lst_addback(&head, new);
		i++;
	}
	return (head);
}
