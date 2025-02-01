/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 15:14:57 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 15:30:05 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*get_env(char *key, t_env_list **head)
{
	t_env_list	*tmp;

	if (!head || !*head || !key)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if (key_found(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
