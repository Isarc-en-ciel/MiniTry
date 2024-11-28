/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:59:12 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/28 13:48:01 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

static	char	*find_env_var(char *var, char **env, int *flag)
{
	t_env_list	*head;
	t_env_list	*ptr;
	char		*expanded_value;

	head = array_to_list(env);
	if (!head)
		*flag = -1;
	ptr = get_env(var, head);
	if (!ptr)
		expanded_value  = "";
	else
	{
		expanded_value = ft_strdup(ptr->value);
		if (!expanded_value)
			*flag = -1;
	}
	free(var);
	var = NULL;
	destroy_lst(&head);
	return (expanded_value);
}

static char	*get_value_to_expand(char *word, int *i)
{
	int		seq_begin;
	char	*var;
	int		count;

	seq_begin = *i;
	count = 0;
	var = NULL;
	*i = *i + 1;
	while (word[*i] && word[*i] != ' ' &&  word[*i] != '$')
	{
		count++;
		*i = *i + 1;;
	}
	var = update_expanded_value(var, word + seq_begin + 1, count);
	if (!var)
		return (NULL);
	return (var);
}

int	expand_env_var(char **retp, char *word, int i, char **env)
{
	char	*var;

	var = get_value_to_expand(word, &i);
	ft_printf("var : %s\n", var);
	if (!var)
	{
		free(*retp);
		*retp = NULL;
		return (-1);
	}
	var = find_env_var(var, env, &i);
	if (i == -1)
	{
		free(var);
		free(*retp);
		return (-1);
	}
	*retp = update_expanded_value(*retp, var, ft_strlen(var));
	return (i);
}
