/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:26:54 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 16:29:32 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_env_list	*free_struct(t_env_list **head, char **tab)
{
	if (head && *head)
		destroy_lst(head);
	if (tab)
		free_tab_char(tab);
	return (NULL);
}

t_env_list	*array_to_list(char **env)
{
	t_env_list	*head;
	t_env_list	*new;
	char		**dico;
	int			i;

	head = NULL;
	i = 0;
	while (env[i])
	{
		dico = ft_split(env[i], '=');
		if (!dico)
			return (free_struct(&head, dico));
		new = new_env_list(dico[0], dico[1]);
		free_tab_char(dico);
		if (!new)
			return ((t_env_list*)free_struct(&head, dico));
		lst_addback(&head, new);
		i++;
	}
	return (head);
}
