/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:09:51 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 14:00:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(t_env_list *head, char *key)
{
	t_env_list	*ptr;

	ptr = head;
	while (ptr)
	{
		if (key_found(key, ptr->key))
			return (ptr->value);
		ptr = ptr->next;
	}
	return (NULL);
}
