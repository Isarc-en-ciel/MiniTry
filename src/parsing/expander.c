/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:29:17 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/28 16:14:44 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expander(t_stock *tab, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < tab[i].nbr_cmd)
	{
		if (expand_cmd(tab[i].cmd, shell) == -1)
			return (-1);
		if (join_cmd(tab[i].cmd) == -1)
			return (-1);
		i++;
	}
	tab = tab_cleaner(tab);
	return (0);
}

int	expand_cmd(t_lexer *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	(void) shell;
	printf("Here\n");
	while (&cmd[i])
	{
		if (cmd[i].type == WORD || cmd[i].type == D_QUOTE)
		{
			if (ft_strcmp(cmd[i].word, '$') == 0)
			{
				printf("Here\n");
				//if (expand_var(shell, &cmd[i].word) == -1)
				//	return (-1);
				if (cmd[i].word == NULL || ft_strlen(cmd[i].word) == 0)
					cmd[i]. is_there_a_space = -1;
			}
		}
		i++;
	}
	return (0);
}

int	join_cmd(t_lexer *cmd)
{
	int	i;
	int	a;

	i = 0;
	a = 1;
	while (&cmd[i++])
	{
		if (cmd[i].is_there_a_space != -1)
		{
			while (&cmd[i + a])
			{
				if ((cmd[i].type == WORD || cmd[i].type == D_QUOTE
						|| cmd[i].type == QUOTE) && ((cmd[i + a].type == WORD
							|| cmd[i + a].type == D_QUOTE
							|| cmd[i + a].type == QUOTE)
						&& cmd[i + a].is_there_a_space == 0))
				{
					cmd[i].word = ft_strjoin(cmd[i].word, cmd[i + a].word, 2);
					if (cmd[i].word == NULL)
						return (-1);
					cmd[i + a].is_there_a_space = -1;
				}
				a++;
			}
		}
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
