/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:24:27 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/17 13:31:00 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* The goal is to expand an input string received  where the ft_strchr(str, '$') returned something
  * it is all the string within QUOTES or D_QUOTES. The goal is to return a new string in which
  * the substring that should be expanded are efficiently transformed. The input can take 
  * the following forms "this part of string should not be expanded but the $USER is $$$$$lol $?"
  * We decide to manage the $$ (another expansion in bash that returns the PID) by ignoring it.
  * 
  * The only expansion that we should manage is the exit status and the environment variable
 */

static int	get_word(char **retp, char *word, int i)
{
	int		count;
	int		seq_begin;

	count = 0;
	seq_begin = i;
	while (word[i] && word[i] != '$')
	{
		i++;
		count++;
	}
	if (!count)
		return (i);
	*retp = update_expanded_value(*retp, word + seq_begin, count);
	return (i);
}

static int	manage_undefined_behavior(char **retp, char *word, int i)
{
	while (word[i] && word[i] == '$'
		&& ((word[i + 1] && word[i + 1] == '$') || (word[i + 1] == '\0')))
	{
		i++;
	}
	*retp = update_expanded_value(*retp, "", 0);
	i++;
	return (i);
}

static int	parse_expansion(char **retp, char *word, int i)
{
	if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '$')
		i = manage_undefined_behavior(retp, word, i);
	else if (word[i] && word[i] == '$' && word[i + 1] == '\0')
	{
		*retp = update_expanded_value(*retp, "$", 1);
		i++;
	}
	else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == ' ')
	{
		*retp = update_expanded_value(*retp, "$ ", 2);
		i += ft_strlen("$ ");
	}
	return (i);
}

static int	get_expansion_status(int i, char **word, char **ret)
{
	if (i == -1)
	{
		if (*word)
			free(*word);
		if (*ret)
			free(*ret);
		return (-1);
	}
	if (*word)
		free(*word);
	*word = *ret;
	return (0);
}

int	expand_var(t_shell *sh, char **wordp)
{
	char		*ret;
	char		*word;
	int			i;

	ret = NULL;
	word = *wordp;
	i = 0;
	while (i != -1 && word && word[i] && (size_t)i < ft_strlen(word))
	{
		if (word && word[i] && word[i] != '$')
			i = get_word(&ret, word, i);
		else
		{
			i = parse_expansion(&ret, word, i);
			if (i == -1 || !word || (size_t)i >= ft_strlen(word) || !word[i])
				break ;
			if (is_the_exit_status(word, i))
				i += expand_exit_status(&ret, sh->exit_status);
			else if (is_an_env_var(word, i))
				i = expand_env_var(&ret, word, i, sh->env);
		}
	}
	i = get_expansion_status(i, wordp, &ret);
	ft_printf("return of expansion : %d; input expanded : %s\n", i, *wordp);
	return (i);
}
