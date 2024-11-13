/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:06:17 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/13 15:57:14 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_darray	*retrieve_cmd(char *input)
{
	t_darray	*tab;
	int			i;
	int			j;
	int			a;

	i = 0;
	j = 0;
	tab = malloc(sizeof(t_darray));
	if (!tab)
		return (NULL);
	if (init_array(tab, 10) == 0)
		return (tab);
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
			return (free_final_array(tab), NULL);
	}
	if (tab->actual_size == 0)
		return (NULL);
	print_token_tab(tab);
	return (tab);
}

int	ft_isspace(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}
