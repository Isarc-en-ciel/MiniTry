/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:02:05 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/25 12:37:39 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redirect(enum e_tokens token)
{
	if (token == REDIR_IN || token == REDIR_OUT
		|| token == REDIR_APP || token == REDIR_HEREDOC)
		return (0);
	return (1);
}

int	is_word_token(enum e_tokens token)
{
	if (token == WORD || token == D_QUOTE || token == QUOTE)
		return (0);
	return (1);
}

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
			if ((is_redirect(tab[i].cmd[j].type) == 0)
				&& (j + 1 >= tab[i].nbr_elem
					|| is_word_token(tab[i].cmd[j + 1].type) == 1))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_first_degree_tab(t_stock *tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (tab[j].cmd)
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
		while (n < tab[j].nbr_elem)
		{
			if (tab[j].cmd[n].word)
				free (tab[j].cmd[n].word);
			n++;
		}
		j++;
	}
	free_first_degree_tab(tab, i);
}
