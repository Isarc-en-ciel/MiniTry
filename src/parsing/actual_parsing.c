/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:58:18 by iwaslet           #+#    #+#             */
/*   Updated: 2024/10/08 15:03:49 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	parsing_starter(t_darray *tokens)
{
	int	i;
	t_stock	*tab;

	i = count_pipes(tokens);
	if (i == -1)
	{
		printf("pipe error\n");
		return (1);
	}
	tab = malloc(sizeof(t_stock) * i);
	if (!tab)
		return (1);
	tab = into_cmds(i, tokens);
	return (0);
}

int	count_pipes(t_darray *tokens)
{
	int	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < tokens->actual_size - 1)
	{
		if (tokens->content[0].type == PIPE)
			return (-1);
		if (tokens->content[j].type == PIPE)
		{
			if (tokens->content[j + 1].type == PIPE)
				return (-1);
			i++;
		}
		j++;
	}
	if (tokens->content[j].type && tokens->content[j].type == PIPE)
		return (-1);
	return (i);
}

t_stock	*into_cmds(int i, t_darray *tokens)
{
	
}
