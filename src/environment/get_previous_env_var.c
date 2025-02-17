/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_previous_env_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:13:27 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/17 13:33:52 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*get_prev_env(t_env_list **head, char *key)
{
	t_env_list	*tmp;

	if (!head || !*head || !key)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if (tmp->next)
		{
			if (key_found(tmp->next->key, key))
				return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
