/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:06:42 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/17 17:46:41 by iwaslet          ###   ########.fr       */
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

t_stock	*error_return(t_darray *tokens, int i)
{
	if (tokens)
	{
		free_final_array(tokens);
	}
	if (i == 1)
	{
		//renvoyer code d'erreur en t_shell
		write (1, "SYNTAX ERROR\n", 13);
	}
	//if (i == 0)
	//EXIT SA MERE shell->exit_status = code erreur approprie
	return (NULL);
}

t_command	*error_parsing(t_stock *tab)
{
	return (NULL);
}
