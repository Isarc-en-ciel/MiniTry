/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:06:17 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/13 16:22:01 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_darray	*retrieve_cmd(char *input)
{
	t_darray	*tab;

	tab = malloc(sizeof(t_darray));
	if (!tab)
		return (NULL);
	if (init_array(tab, 10) == 0)
		return (tab);
	if (retrieve_loop(input, tab, 0, 0) == 1)
	{
		free_final_array(tab);
		return (NULL);
	}
	if (tab->actual_size == 0)
		return (NULL);
	print_token_tab(tab);
	return (tab);
}

int	retrieve_loop(char *input, t_darray *tab, int i, int j)
{
	int	a;

	while (input[i])
	{
		a = 0;
		if (ft_isspace(input[i]) == 1)
			i++;
		else if (input[i] == '|')
			a = retrieve_pipe(input, &i, &j, tab);
		else if (input[i] == '<')
			a = retrieve_in(input, &i, &j, tab);
		else if (input[i] == '>')
			a = retrieve_out(input, &i, &j, tab);
		else if (input[i] == '\"')
			a = retrieve_dquotes(input, &i, &j, tab);
		else if (input[i] == '\'')
			a = retrieve_squotes(input, &i, &j, tab);
		else
			a = retrieve_word(input, &i, &j, tab);
		if (a == 1)
			return (1);
	}
	return (0);
}

int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}
