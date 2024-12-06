/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:09:51 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/02 15:14:37 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(t_env_list *head, char *key)
{
	t_env_list	*ptr;

	ptr = head;
	while (ptr)
	{
		if (!ft_strncmp(key, ptr->key, ft_strlen(key)) 
			&& !ft_strncmp(key, ptr->key, ft_strlen(ptr->key)))
		{
			return (ptr->value);
		}
		ptr = ptr->next;
	}
	return (NULL);
}

