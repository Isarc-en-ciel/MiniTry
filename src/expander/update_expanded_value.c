/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_expanded_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:54:38 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/27 19:12:20 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

char	*update_expanded_value(char *ret, char *word, int count)
{
	char	*var;

	var = NULL;
	var = ft_calloc(count + 1, sizeof(char));
	ft_memcpy(var, word, count);
	if (!var)
	{
		free(ret);
		return (NULL);
	}
	if (!ret)
		ret = var;
	else
	{
		ret = ft_strjoin(ret, var, BOTH_MALLOC);
		if (!ret)
			return (NULL);
	}
	return (ret);
}