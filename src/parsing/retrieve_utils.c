/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:46:36 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/19 19:02:53 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	retrieve_pipe(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_pipe(input, i, tab->content[*j]);
	tab->actual_size++;
	*j += 1;
	return (0);
}

int	retrieve_in(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_redirect_in(input, i, tab->content[*j]);
	tab->actual_size++;
	*j += 1;
	return (0);
}

int	retrieve_out(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_redirect_out(input, i, tab->content[*j]);
	tab->actual_size++;
	*j += 1;
	return (0);
}

int	retrieve_dquotes(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_doubleq(input, i, tab->content[*j]);
	if (!tab->content[*j].word)
	{
		if (tab->content[*j].is_there_a_space == -1)
			error_fct(tab, 1);
		else
			error_fct(tab, 0);
		return (1);
	}
	tab->actual_size++;
	*j += 1;
	return (0);
}

int	retrieve_squotes(char *input, int *i, int *j, t_darray *tab)
{
	if (reserve_array(tab) == 1)
		return (-1);
	tab->content[*j] = create_simpleq(input, i, tab->content[*j]);
	if (!tab->content[*j].word)
	{
		if (tab->content[*j].is_there_a_space == -1)
			error_fct(tab, 1);
		else
			error_fct(tab, 0);
		return (1);
	}
	tab->actual_size++;
	*j += 1;
	return (0);
}
