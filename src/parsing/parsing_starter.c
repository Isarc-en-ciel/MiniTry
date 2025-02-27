/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_starter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:58:18 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/27 11:27:49 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stock	*parsing_starter(t_darray *tokens, t_stock	*tab, t_shell *shell)
{
	int		i;

	i = count_pipes(tokens) + 1;
	if (i == 0)
		return (error_return(tokens, 1, shell));
	if (i > 300)
		return (error_return(tokens, 2, shell));
	tab = malloc(sizeof(t_stock) * i);
	if (!tab)
		return (error_return(tokens, 0, shell));
	if (into_cmds(i, tokens, tab) == -1)
	{
		free(tab);
		return (error_return(tokens, 0, shell));
	}
	if (check_grammar(tab, i) == 1)
	{
		free_second_degree_tab(tab, tab[0].nbr_cmd);
		return (error_return(tokens, 1, shell));
	}
	return (tab);
}

int	count_pipes(t_darray *tokens)
{
	int		i;
	size_t	j;

	i = 0;
	j = 0;
	while (j < tokens->actual_size - 1)
	{
		if (tokens->content[0].type == PIPE)
			return (-1);
		if (tokens->content[j].type == PIPE)
		{
			if (tokens->content[j + 1].type == PIPE)
				return (-1);
			i++;
		}
		if (i < 0 || i > INT_MAX)
			return (301);
		j++;
	}
	if (tokens->content[j].type && tokens->content[j].type == PIPE)
		return (-1);
	return (i);
}

int	into_cmds(int i, t_darray *tokens, t_stock *tab)
{
	int	j;
	int	l;

	j = 0;
	l = 0;
	if (nbr_elem_cmd(i, tokens, tab) == -1)
	{
		free_first_degree_tab(tab, i);
		return (-1);
	}
	while (j < i)
	{
		if (fill_cmb_tab(&j, &l, tokens, tab) == -1)
		{
			free_second_degree_tab(tab, i);
			return (-1);
		}
		l++;
		j++;
	}
	return (0);
}

int	fill_cmb_tab(int *j, int *l, t_darray *tokens, t_stock *tab)
{
	int	n;

	n = 0;
	while (n < tab[*j].nbr_elem && (size_t)(*l) < tokens->actual_size)
	{
		tab[*j].cmd[n].is_there_a_space
			= tokens->content[*l].is_there_a_space;
		tab[*j].cmd[n].type = tokens->content[*l].type;
		if (ft_strlen(tokens->content[*l].word) == 0
			&& !tokens->content[*l].word)
			tab[*j].cmd[n].word = NULL;
		else
		{
			tab[*j].cmd[n].word = ft_calloc(
					(ft_strlen(tokens->content[*l].word) + 1), sizeof(char));
			if (!tab[*j].cmd[n].word)
				return (-1);
			tab[*j].cmd[n].word = ft_memcpy(tab[*j].cmd[n].word,
					tokens->content[*l].word,
					ft_strlen(tokens->content[*l].word));
		}
		n++;
		*l += 1;
	}
	return (0);
}

int	nbr_elem_cmd(int i, t_darray *tokens, t_stock *tab)
{
	int		j;
	int		cmd_size;
	size_t	n;

	j = 0;
	n = 0;
	while (j < i)
	{
		cmd_size = 0;
		while (n < tokens->actual_size && tokens->content[n].type != PIPE)
		{
			n++;
			cmd_size++;
		}
		tab[j] = (t_stock){0};
		tab[j].nbr_elem = cmd_size;
		tab[j].nbr_cmd = i;
		tab[j].cmd = ft_calloc((tab[j].nbr_elem), sizeof(t_lexer));
		if (!tab[j].cmd)
			return (-1);
		n++;
		j++;
	}
	return (0);
}
