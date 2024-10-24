/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actual_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:58:18 by iwaslet           #+#    #+#             */
/*   Updated: 2024/10/15 16:09:30 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	parsing_starter(t_darray *tokens)
{
	int		i;
	t_stock	*tab;

	i = count_pipes(tokens) + 1;
	if (i == 0)
	{
		printf("pipe error\n");
		return (1);
	}
	tab = malloc(sizeof(t_stock) * i);
	if (!tab)
		return (1);
	if (into_cmds(i, tokens, tab) == -1)
	{
		printf("malloc error\n");
		return (1);
	}
	return (0);
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
	if (nbr_elem_cmd(i, tokens, tab) == 1)
		return (1);
	while (j < i)
	{
		if (fill_cmb_tab(&j, &l, tokens, tab) == -1)
			return (-1);
		l++;
		j++;
	}
	return (0);
}

int	fill_cmb_tab(int *j, int *l, t_darray *tokens, t_stock *tab)
{
	int	n;

	n = 0;
	while (n < tab[*j].nbr_elem)
	{
		tab[*j].cmd[n].is_there_a_space
			= tokens[*l].content->is_there_a_space;
		tab[*j].cmd[n].type = tokens[*l].content->type;
		tab[*j].cmd[n].word = malloc(sizeof(char)
				* ft_strlen(tokens[*l].content->word));
		if (!tab[*j].cmd[n].word)
			return (-1);
		tab[*j].cmd[n].word = ft_memcpy(tab[*j].cmd[n].word,
				tokens[*l].content->word, ft_strlen(tokens[*l].content->word));
		n++;
		l++;
	}
	return (0);
}

int	nbr_elem_cmd(int i, t_darray *tokens, t_stock *tab)
{
	int	j;
	int	n;

	j = 0;
	while (j < i)
	{
		n = 0;
		while (tokens->content[n].type != PIPE)
			n++;
		tab[j].nbr_elem = n;
		tab[j].cmd = malloc(sizeof(t_lexer) * n);
		if (!tab[j].cmd)
			return (1);
		n++;
		j++;
	}
	return (0);
}
