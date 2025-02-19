/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:46:51 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/19 19:02:59 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	retrieve_word(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_word(input, i, tab->content[*j]);
	if (!tab->content[*j].word)
	{
		error_fct(tab, 0);
		return (1);
	}
	tab->actual_size++;
	*j += 1;
	return (0);
}
