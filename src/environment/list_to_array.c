/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:29:05 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 17:37:04 by csteylae         ###   ########.fr       */
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

char **list_to_array(t_env_list **head)
{
	char		**env;
	t_env_list	*tmp;
	int			i;

	tmp = *head;
	env = NULL;
	i = 0;
	env = malloc(sizeof(*env) * (get_list_size(*head) + 1));
	if (!env)
		return (free_struct(head, env));
	while (tmp)
	{
		env[i] = ft_strjoin(tmp->key, "=", NO_MALLOC);
		if (!env[i])
			return (free_struct(head, env));
		env[i] = ft_strjoin(env[i], tmp->value, S1_MALLOC);
		if (!env[i])
			return (free_struct(head, env));
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_print_list(t_env_list *head)
{
	t_env_list	*tmp;

	tmp = head;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
