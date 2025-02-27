/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darray_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:48:50 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/27 12:36:55 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_array(t_darray *darray, size_t block_size)
{
	darray->block = block_size;
	darray->max_size = block_size;
	darray->actual_size = 0;
	darray->content = ft_calloc(block_size, sizeof(t_lexer));
	if (!darray->content)
		return (0);
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
		if (darray->content[i].word)
			free(darray->content[i].word);
		i++;
	}
}

t_darray	realloc_array(t_darray *darray)
{
	t_lexer	*new_content;
	size_t	i;

	i = 0;
	darray->max_size = darray->max_size + darray->block;
	new_content = ft_calloc(darray->max_size, sizeof(t_lexer));
	if (!new_content)
	{
		darray->max_size = 0;
		return (*darray);
	}
	while (i < darray->actual_size)
	{
		if (copy_token(darray->content[i], &new_content[i]) == -1)
		{
			darray->max_size = 0;
			return (*darray);
		}
		free (darray->content[i].word);
		i++;
	}
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
