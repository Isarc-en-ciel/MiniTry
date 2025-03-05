/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:05 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/05 19:03:09 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	*free_struct(t_env_list **head, char **str_tab)
{
	if (head && *head)
		destroy_lst(head);
	if (str_tab)
		free_tab_char(str_tab);
	return (NULL);
}

static char	*join_key_value(t_env_list *tmp)
{
	char	*str;

	str = ft_strjoin(tmp->key, "=", NO_MALLOC);
	if (!str)
		return (NULL);
	str = ft_strjoin(str, tmp->value, S1_MALLOC);
	if (!str)
		return (NULL);
	return (str);
}

char	*list_to_str(t_env_list *tmp)
{
	char	*str;

	str = NULL;
	if (tmp->value)
	{
		str = join_key_value(tmp);
		if (!str)
			return (NULL);
	}
	else
	{
		str = ft_strdup(tmp->key);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	**list_to_array(t_env_list **head)
{
	char		**env;
	t_env_list	*tmp;
	int			i;

	tmp = *head;
	i = 0;
	if (*head == NULL)
		return (NULL);
	env = malloc(sizeof(*env) * (get_list_size(*head) + 1));
	if (!env)
		return (free_struct(head, env));
	while (tmp)
	{
		env[i] = list_to_str(tmp);
		if (!env[i])
			return (free_struct(head, env));
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
