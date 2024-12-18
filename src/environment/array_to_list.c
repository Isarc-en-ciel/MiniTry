/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:26:54 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/12 12:38:48 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env_list	*get_env_entry(char *str)
{
	t_env_list	*new;
	char		**pair_key_value;
	
	new = NULL;
	pair_key_value = NULL;
	if (!ft_strchr(str, '='))
	{
		new = new_env_list(str, NULL, false);
	}
	else
	{
		pair_key_value = ft_split(str, '=');
		if (!pair_key_value)
			return (NULL);
		if (pair_key_value[1] == NULL)
			new = new_env_list(pair_key_value[0], "", true);
		else
			new = new_env_list(pair_key_value[0], pair_key_value[1], true);
		free_tab_char(pair_key_value);
	}
	return (new);
}

t_env_list	*array_to_list(char **env)
{
	t_env_list	*head;
	t_env_list	*new;
	int			i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		new = get_env_entry(env[i]);
		if (!new)
		{
			destroy_lst(&head);
			return (NULL);
		}
		lst_addback(&head, new);
		i++;
	}
	ft_printf("%i\n", i);
	return (head);
}
