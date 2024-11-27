/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:24:27 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/27 19:24:49 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	int		seq_begin;
	char	*var;

	seq_begin = i;
	var = NULL;
	while (word[i] && word[i] == '$' && ((word[i + 1] && word[i + 1] == '$') || (word[i + 1] == '\0')))
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
	{
		i = manage_undefined_behavior(retp, word, i); 
	}
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

char	*expand_var(t_shell *sh, char *word)
{
	char	*ret;
	size_t		i;

	ret = NULL;
	i = 0;
	while(word[i] && i <= ft_strlen(word))
	{
		if (word[i] && word[i] != '$')
		{
			i =  get_word(&ret, word, i);
		}
		else 
		{
			i = parse_expansion(&ret, word, i);
			if (!word[i])
				break ;
			if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '?')
			{
				i += expand_exit_status(&ret, sh->exit_status);
			}
			else if (word[i] && word[i] == '$')
			{
				i = expand_env_var(&ret, word, i, sh->env);
			}
		}
		if ((size_t)i >= ft_strlen(word))
			break ;
	}
	ft_printf("return : %s\n", ret);
	return (ret);
}


//char	*expand_var(t_shell *sh, char *word)
//{
//	char	*ret;
//	size_t		i;
//
//	ret = NULL;
//	i = 0;
//	while(word[i] && i <= ft_strlen(word))
//	{
//		if (word[i] && word[i] != '$')
//		{
//			i =  get_word(&ret, word, i);
//		}
//		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '?')
//		{
//			i += expand_exit_status(&ret, sh->exit_status);
//		}
//		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == ' ')
//		{
//			ret = update_expanded_value(ret, "$ ", 2);
//			i += ft_strlen("$ ");
//		}
//		else if (word[i] && word[i] == '$' && word[i + 1] == '\0')
//		{
//			ret = update_expanded_value(ret, "$", 1);
//			i++;
//		}
//		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '$')
//		{
//			i = manage_undefined_behavior(&ret, word, i); 
//		}
//		else
//		{ 
//			i = find_env_var(&ret, word, i, sh->env);
//		}
//		if (i >= ft_strlen(word))
//			break ;
//	}
//	ft_printf("return : %s\n", ret);
//	return (ret);
//}
