/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:46:51 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/13 15:59:29 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	retrieve_word(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (1);
	tab->content[*j] = create_word(input, i, tab->content[*j]);
	if (!tab->content[*j].word)
	{
		error_fct(tab);
		return (1);
	}
	tab->actual_size++;
	*j += 1;
	return (0);
}

int	error_fct(t_darray *tab)
{
	write (1, "SYNTAX ERROR\n", 13);
	if (tab->content)
		free_temp_array(tab);
	return (0);
}
