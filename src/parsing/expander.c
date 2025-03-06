/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:29:17 by iwaslet           #+#    #+#             */
/*   Updated: 2025/03/06 12:37:15 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_stock	*expander(t_stock *tab, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < tab[0].nbr_cmd)
	{
		if (expand_cmd(tab[i].cmd, shell, tab[i].nbr_elem) == -1)
			return (NULL);
		if (join_cmd(tab[i].cmd, tab[i].nbr_elem, 0, 1) == -1)
			return (NULL);
		i++;
	}
	tab = tab_cleaner(tab);
	if (tab == NULL)
		return (NULL);
	return (tab);
}

int	expand_cmd(t_lexer *cmd, t_shell *shell, int size)
{
	int	i;

	i = 0;
	(void) shell;
	while (i < size)
	{
		if (cmd[i].type == WORD || cmd[i].type == D_QUOTE)
		{
			if (ft_strcmp(cmd[i].word, '$') == 0)
			{
				if (expand_var(shell, &cmd[i].word) == -1)
					return (-1);
				if (cmd[i].word == NULL || ft_strlen(cmd[i].word) == 0)
					cmd[i].is_there_a_space = -1;
			}
		}
		i++;
	}
	return (0);
}

int	join_cmd(t_lexer *cmd, int size, int i, int a)
{
	while (i < size)
	{
		a = 1;
		while (i + a < size && is_word_token(cmd[i + a].type) == 0)
		{
			if ((cmd[i].is_there_a_space != -1)
				&& (is_word_token(cmd[i].type) == 0)
				&& (is_word_token(cmd[i + a].type) == 0)
				&& cmd[i + a].is_there_a_space == 0)
			{
				cmd[i].word = ft_strjoin(cmd[i].word, cmd[i + a].word, '1');
				if (cmd[i].word == NULL)
					return (-1);
				change_type(&cmd[i], cmd[i + a]);
				cmd[i + a].is_there_a_space = -1;
				a++;
			}
			else
				i++;
			}
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s, char n)
{
	unsigned int	i;
	unsigned int	l;

	i = 0;
	l = ft_strlen (s);
	while (i < l)
	{
		if (s[i] == n)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}
