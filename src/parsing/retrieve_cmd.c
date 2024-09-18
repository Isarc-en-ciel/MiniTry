/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:06:17 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/18 17:06:18 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_darray	retrieve_cmd(char *input)
{
	t_darray	tab;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (init_array(&tab, 10) == 0)
		return (tab);
	while (input[i]) //j'itere ou sur j ptdr ???
	{
		if (ft_isspace(input[i]) == 0) //mettre un flag au ca ou j'ai que des espaces (check que j'ai bien malloc tab.content)
			i++;
		else if (input[i] == '|')
		{
			reserve_array(&tab);
			tab.content[j] = create_pipe(input, &i, tab.content[j]);
			tab.actual_size++;
			j++;
		}
		else if (input[i] == '<')
		{
			reserve_array(&tab);
			tab.content[j] = create_redirect_in(input, &i, tab.content[j]);
			tab.actual_size++;
			j++;
		}
		else if (input[i] == '>')
		{
			reserve_array(&tab);
			tab.content[j] = create_redirect_out(input, &i, tab.content[j]);
			tab.actual_size++;
			j++;
		}
		else if (input[i] == '\"')
		{
			reserve_array(&tab);
			tab.content[j] = create_doubleq(input, &i, tab.content[j]);
			if (!tab.content[j].word)
				error_fct(tab);
			tab.actual_size++;
			j++;
		}
		else if (input[i] == '\'')
		{
			reserve_array(&tab);
			tab.content[j] = create_simpleq(input, &i, tab.content[j]);
			if (!tab.content[j].word)
				error_fct(tab);
			tab.actual_size++;
			j++;
		}
		else
		{
			reserve_array(&tab);
			tab.content[j] = create_word(input, &i, tab.content[j]);
			if (!tab.content[j].word)
				error_fct(tab);
			tab.actual_size++;
			j++;
		}
    }
	return (tab);
}

int	init_array(t_darray *darray, size_t block_size)
{
	darray->block = block_size;
	darray->max_size = block_size;
	darray->actual_size = 0;
	darray->content = malloc(sizeof(t_lexer) * block_size);
	if (!darray->content)
		return (0);
	return (1);
}

void	reserve_array(t_darray *darray)
{
	if (darray->actual_size >= darray->max_size)
		realloc_array(darray);
}

void	free_temp_array(t_darray *darray)
{
	int	i;

	i = 0;
	while (i < darray->actual_size)
	{
		free(darray->content[i].word);
		i++;
	}
	free(darray->content);
}

t_darray	realloc_array(t_darray *darray)
{
	t_lexer	*new_content;
	int		i;

	i = 0;
	darray->max_size = darray->max_size + darray->block;
	new_content = malloc(sizeof(t_lexer) * darray->max_size);
	while (&darray->content[i])
	{
		new_content[i] = darray->content[i];
		i++;
	}
	free_temp_array(darray);
	darray->content = new_content;
	return (*darray);
}

int	error_fct(t_darray tab)
{
	write (1, "SYNTAX ERROR\n", 13);
	if (&tab)
		free_temp_array(&tab);
	return (1);
}

int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (0);
	return (1);
}
