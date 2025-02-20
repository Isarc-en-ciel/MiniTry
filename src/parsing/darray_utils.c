/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:48:50 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/20 14:45:36 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_array(t_darray *darray, size_t block_size)
{
	darray->block = block_size;
	darray->max_size = block_size;
	darray->actual_size = 0;
	darray->content = malloc(sizeof(t_lexer) * block_size);
	if (!darray->content)
		return (0);
	ft_bzero(darray->content, sizeof(t_lexer) * darray->max_size);
	return (1);
}

int	reserve_array(t_darray *darray)
{
	if (darray->actual_size >= darray->max_size)
	{
		realloc_array(darray);
		if (darray->max_size == 0)
		{
			free_temp_array(darray);
			return (1);
		}
	}
	return (0);
}

void	free_temp_array(t_darray *darray)
{
	size_t	i;

	i = 0;
	while (i < darray->actual_size)
	{
		free(darray->content[i].word);
		i++;
	}
}

t_darray	realloc_array(t_darray *darray)
{
	t_lexer	*new_content;

	darray->max_size = darray->max_size + darray->block;
	new_content = malloc(sizeof(t_lexer) * darray->max_size);
	if (!new_content)
	{
		darray->max_size = 0;
		return (*darray);
	}
	ft_bzero(new_content, sizeof(t_lexer) * darray->max_size);
	ft_memcpy(new_content, darray->content, sizeof(t_lexer) * darray->max_size);
	free(darray->content);
	darray->content = new_content;
	return (*darray);
}

void	free_final_array(t_darray *darray)
{
	free_temp_array(darray);
	free (darray->content);
	free (darray);
}
