/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:02:05 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/20 15:00:55 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_grammar(t_stock *tab, int cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds)
	{
		j = 0;
		while (j < tab[i].nbr_elem)
		{
			if ((tab[i].cmd[j].type == REDIR_IN
					|| tab[i].cmd[j].type == REDIR_OUT
					|| tab[i].cmd[j].type == REDIR_APP
					|| tab[i].cmd[j].type == REDIR_HEREDOC)
				&& tab[i].cmd[j + 1].type != WORD)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	free_first_degree_tab()
{
	
}

int	free_second_degree_tab()
{
	
}

/* ou est ce que j'initie/remplis le t_shell ?
ou est ce que je le revoie/recupere ?
fonction supplementaire dans le main pour mettre toutes 
les fcts de parsing pour retourner l'erreur et le t_shell plus facilement ?*/