/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:58:18 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/30 18:43:01 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	parsing_starter(t_darray *tokens)
{
	int	i;

	i = count_pipes(tokens);
	if (i == -1)
	{
		printf("pipe error\n");
		return (1);
	}
	printf("nbr of pipes: %d\n", i);
	return (0);
}

int	count_pipes(t_darray *tokens)
{
	int	i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < tokens->actual_size)
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
	//if (tokens->content[j].type == PIPE)
//		return (-1); comment faire pour detecter dernier element est un pipe ?
	return (i);
}
