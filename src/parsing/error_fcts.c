/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:06:42 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/19 15:27:31 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_fct(t_darray *tab, int i)
{
	if (i == 1)
		write (1, "SYNTAX ERROR\n", 13);
	if (tab->content)
		free_temp_array(tab);
	if (i == 0)
		exit (EXIT_FAILURE);
	return (0);
}

t_stock	*error_return(t_darray *tokens, int i, t_shell *shell)
{
	if (tokens)
	{
		free_final_array(tokens);
	}
	if (i == 1)
	{
		shell->exit_status = 2;
		write (1, "SYNTAX ERROR\n", 13);
	}
	if (i == 0)
		exit (EXIT_FAILURE);
	return (NULL);
}

t_command	*error_parsing(t_stock *tab, int i, t_shell *shell)
{
	
	if (i == 1)
	{
		shell->exit_status = 2;
		write (1, "SYNTAX ERROR\n", 13);
	}
	if (tab)
		free_second_degree_tab(tab, tab[0].nbr_cmd);
	exit (EXIT_FAILURE);
	return (NULL);
}
