/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:05 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/13 19:53:29 by csteylae         ###   ########.fr       */
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

char	**list_to_array(t_env_list **head)
{
	char		**env;
	t_env_list	*tmp;
	int			i;

	tmp = *head;
	i = 0;
	env = malloc(sizeof(*env) * (get_list_size(*head) + 1));
	if (!env)
		return (free_struct(head, env));
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=", NO_MALLOC);
		if (!env[i])
			return (free_struct(head, env));
		if (tmp->value)
			env[i] = ft_strjoin(env[i], tmp->value, S1_MALLOC);
		else
			env[i] = ft_strdup(tmp->key);
		if (!env[i])
			return (free_struct(head, env));
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
