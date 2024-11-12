/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:06:17 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/12 15:06:02 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_darray	*retrieve_cmd(char *input)
{
	t_darray	*tab;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tab = malloc(sizeof(t_darray));
	if (!tab)
		return (NULL);
	if (init_array(tab, 10) == 0)
		return (tab);
	while (input[i])
	{
		if (ft_isspace(input[i]) == 1)
			i++;
		else if (input[i] == '|')
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_pipe(input, &i, tab->content[j]);
			tab->actual_size++;
			j++;
		}
		else if (input[i] == '<')
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_redirect_in(input, &i, tab->content[j]);
			tab->actual_size++;
			j++;
		}
		else if (input[i] == '>')
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_redirect_out(input, &i, tab->content[j]);
			tab->actual_size++;
			j++;
		}
		else if (input[i] == '\"')
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_doubleq(input, &i, tab->content[j]);
			if (!tab->content[j].word)
				return (error_fct(tab), NULL);
			tab->actual_size++;
			j++;
		}
		else if (input[i] == '\'')
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_simpleq(input, &i, tab->content[j]);
			if (tab->content[j].word == NULL)
				return (error_fct(tab), NULL);
			tab->actual_size++;
			j++;
		}
		else
		{
			if (reserve_array(tab) == 1)
				exit (1);
			tab->content[j] = create_word(input, &i, tab->content[j]);
			if (!tab->content[j].word)
				return (error_fct(tab), NULL);
			tab->actual_size++;
			j++;
		}
	}
	if (tab->actual_size == 0)
		return (NULL);
	//print_token_tab(tab);
	return (tab);
}

int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}
