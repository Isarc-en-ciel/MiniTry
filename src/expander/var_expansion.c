/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:24:27 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/27 17:09:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*update_return_value(char *ret, char *word, int count)
{
	char	*var;

	var = NULL;
	var = ft_calloc(count + 1, sizeof(char));
	ft_memcpy(var, word, count);
	if (!var)
	{
		free(ret);
		return (NULL);
	}
	if (!ret)
		ret = var;
	else
	{
		ret = ft_strjoin(ret, var, BOTH_MALLOC);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

int	get_word(char **retp, char *word, int i)
{
	char	*var;
	int		count;
	int		seq_begin;

	var = NULL;
	count = 0;
	seq_begin = i;
	while (word[i]  && word[i] != '$')
	{
		i++;
		count++;
	}
	if (!count)
		return (i);
	*retp = update_return_value(*retp, word + seq_begin, count);
	return (i);
}

int	expand_exit_status(char **retp, int exit_status)
{
	char	*var;

	var = ft_itoa(exit_status);
	if (!var)
	{
		free(*retp);
		*retp = NULL;
		return (-1);
	}
	*retp = update_return_value(*retp, var, ft_strlen(var));
	if (!*retp)
		return (0);
	return (2);
}

int	manage_undefined_behavior(char **retp, char *word, int i)
{
	int		count;
	int		seq_begin;
	char	*var;

	count = 0;
	seq_begin = i;
	var = NULL;
	while (word[i] && word[i] == '$' && ((word[i + 1] && word[i + 1] == '$') || (word[i + 1] == '\0')))
	{
		i++;
		count++;
	}
	*retp = update_return_value(*retp, word + seq_begin, count);
	return (i);
}

int	find_env_var(char **retp, char *word, int i, char **env)
{
	int		seq_begin;
	char	*var;
	int		count;
	t_env_list	*head;
	t_env_list	*ptr;

	seq_begin = i;
	count = 0;
	var = NULL;
	ptr = NULL;
	head = array_to_list(env);
	if (!head)
	{
		free(*retp);
		*retp = NULL;
		return (-1);
	}
	i++;
	while (word[i] && word[i] != ' ' && word[i] != '$')
	{
		count++;
		i++;
	}
	var = update_return_value(var, word + seq_begin + 1, count ); //word + seq_begin + 1 to remove the $ from the str
	if (!var)
	{
		free(*retp);
		*retp = NULL;
		return (-1);
	}
	ptr = get_env(var, head);
	if (!ptr)
	{
		free(var);
		var = "";
	}
	else
		var = ptr->value;
	*retp = update_return_value(*retp, var, ft_strlen(var));
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
		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '?')
		{
			i += expand_exit_status(&ret, sh->exit_status);
		}
		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == ' ')
		{
			ret = update_return_value(ret, "$ ", 2);
			i += ft_strlen("$ ");
		}
		else if (word[i] && word[i] == '$' && word[i + 1] == '\0')
		{
			ret = update_return_value(ret, "$", 1);
			i++;
		}
		else if (word[i] && word[i] == '$' && word[i + 1] && word[i + 1] == '$')
		{
			i = manage_undefined_behavior(&ret, word, i); 
		}
		else
		{ 
			i = find_env_var(&ret, word, i, sh->env);
		}
		if (i >= ft_strlen(word))
			break ;
	}
	ft_printf("return : %s\n", ret);
	return (ret);
}
