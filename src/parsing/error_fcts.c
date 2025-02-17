/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:06:42 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/17 14:43:02 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_fct(t_darray *tab)
{
	write (1, "SYNTAX ERROR\n", 13);
	if (tab->content)
		free_temp_array(tab);
	return (0);
}

t_stock	*error_return(t_darray *tab, int i)
{
	if (i == 1)
		write (1, "SYNTAX ERROR\n", 13);
	free_final_array(tab);
	return (NULL);
}

t_command	*error_parsing(t_stock *tab)
{
	free(tab); //bien free comme il faut la ?
	return (NULL);
}
