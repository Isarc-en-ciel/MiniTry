/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:02:05 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/14 11:37:42 by iwaslet          ###   ########.fr       */
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
			if (j + 1 < tab[i].nbr_elem)
			{
				if ((tab[i].cmd[j].type == REDIR_IN
					|| tab[i].cmd[j].type == REDIR_OUT
					|| tab[i].cmd[j].type == REDIR_APP
					|| tab[i].cmd[j].type == REDIR_HEREDOC)
					&& (tab[i].cmd[j + 1].type == WORD 
					|| tab[i].cmd[j + 1].type == D_QUOTE 
					|| tab[i].cmd[j + 1].type == QUOTE))
					ft_print_redir_type(tab[i].cmd[j + 1].type);
				j++;
			}
			else
				return (1);
		}
		i++;
	}
	return (0);
}

void	free_first_degree_tab(t_stock *tab, int i)
{
	int	j;

	j = 0;
	while (j < i && tab[j].cmd)
	{
		free (tab[j].cmd);
		j++;
	}
	free (tab);
}

void	free_second_degree_tab(t_stock *tab, int i)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	while (j < i && tab[j].cmd)
	{
		while (n < tab[j].nbr_elem && tab[j].cmd[n].word)
		{
			free (tab[j].cmd[n].word);
			n++;
		}
		j++;
	}
	free_first_degree_tab(tab, i);
}

/* ou est ce que j'initie/remplis le t_shell ?
ou est ce que je le revoie/recupere ?
fonction supplementaire dans le main pour mettre toutes 
les fcts de parsing pour retourner l'erreur et le t_shell plus facilement ?*/