/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:17:35 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/28 16:13:08 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stock	*tab_cleaner(t_stock *tab)
{
	int		i;
	t_stock	*new_tab;

	i = 0;
	new_tab = malloc(sizeof(tab[i].nbr_cmd));
	if (!new_tab)
		return (NULL);
	while (i < tab[i].nbr_cmd)
	{
		if (clean_cmd(tab[i].cmd, &new_tab[i].cmd) == -1)
			return (NULL);
		i++;
	}
	free_second_degree_tab(tab, tab[i].nbr_cmd);
	return (new_tab);
}

int	clean_cmd(t_lexer *cmd, t_lexer **new_cmd)
{
	int	i;

	i = 0;
	if (count_new_elem(cmd) == 0)
		return (-1);
	new_cmd = malloc(sizeof(t_lexer) * count_new_elem(cmd));
	if (!new_cmd)
		return (-1);
	while (&cmd[i])
	{
		if (cmd[i].is_there_a_space != -1)
		{
			if (copy_token(&cmd[i], &new_cmd[i]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	count_new_elem(t_lexer *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (&cmd[i])
	{
		if (cmd[i].is_there_a_space != -1)
			n++;
		i++;
	}
	return (n);
}

int	copy_token(t_lexer *cmd, t_lexer **new_cmd)
{
	int	i;

	(*new_cmd)->is_there_a_space = cmd->is_there_a_space;
	(*new_cmd)->type = cmd->type;
	(*new_cmd)->word = NULL;
	if (cmd->word)
	{
		i = ft_strlen(cmd->word);
		(*new_cmd)->word = malloc(sizeof(char *) * i);
		if (!(*new_cmd)->word)
			return (-1);
		(*new_cmd)->word = ft_strcpy(cmd->word, (*new_cmd)->word);
	}
	return (0);
}
