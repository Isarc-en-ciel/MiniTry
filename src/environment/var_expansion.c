/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:12:43 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/26 18:25:13 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:12:35 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/26 18:12:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:35:14 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/26 18:10:36 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:35:14 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/26 17:35:14 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:24:27 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/26 17:34:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//char    *expand_var(t_shell *shell, char *word)
//{
//	char		*value_to_expand;
//	t_env_list	*head;
//	t_env_list	*ptr;
//
//	value_to_expand = ft_strchr(word, '$');
//	head = array_to_list(shell->env);
//	if (!head)
//		return (NULL);
//	ptr = get_env(value_to_expand, head);
//	if (ptr)
//		value_to_expand = ptr->value;
//	else
//		value_to_expand = NULL;
//	return (NULL);
//}
//
//
//int	get_expansion_size(char *word)
//{
//	int	i;
//	int	count;
//
//	i = 0;
//	count = 0;
//	while (word[i])
//	{
//		if (word[i] == '$' && (word[i + 1] && word[i + 1] != '$'))
//			count++;
//		i++;
//	}
//	ft_printf("COUNT :%d\n", count);
//	return (count);
//}
//
//char	**expansion_list(char *word)
//{
//	int	i;
//	char	*initial_word;
//	char	*new_word;
//
//
//	i = 0;
//	int	j = 0;
//	initial_word = NULL;
//	while (word[i] && word[i] != '$')
//		i++;
//	if (i != 0)
//	{
//		initial_word = calloc(sizeof(char), i + 1);
//		ft_memcpy(initial_word, word, i);
//		word = word + i;
//	}
//	while (word[i])
//	{
//		if (word[i] == '$')
//		{
//			j = 0;
//			while (word[i] && (word[i] != '$' || word[i] != ' '))
//			{
//				j++;
//				i = i + j;
//			}
//			if (word[i])
//			{
//				new_word = calloc(sizeof(char), j + 1); 
//				ft_memcpy(new_word, word, j);
//				new_word = ft_strjoin(initial_word, new_word, NO_MALLOC);
//				//find
//				//replace
//				//join in a new value
//			}
//			else 
//				break;
//		}
//		*word = *(word + i);
//		i = 0;
//		ft_printf("word + i : %s\n", word);
//		ft_printf("word + i : %s\n", word);
//	}
//	return (NULL);
//}
char    *expand_var(t_shell *shell, char *word)
{
	t_env_list	*head;
	t_env_list	*ptr;
	char	*ret;
	int		i;
	char	*new_word;

	i = 0;
	ret = NULL;
	ptr = NULL;
	new_word = 0;
	head = array_to_list(shell->env);
	if (!head)
		return (NULL);
	if (word[i] != '$')
	{
		while (word[i] && (word[i] != '$' || word[i] != ' '))
			i++;
		ret = calloc(sizeof(char), i + 1);
		ft_memcpy(ret, word, i);
	}
	else if (word[i] == '$' && word[i + 1] && word[i + 1] == '?')
	{
		ret = ft_itoa(shell->exit_status);
	}
	else
	{
		int	j = 1;
		while (word[i] && word[i] == '$')
			i++;
		word = word + i;
		 i = 0;
		ft_printf("word + i : %s\n", word);
		while (word[i] && (word[i] != '$' || word[i] == ' '))
		{
			j++;
			i++;
		}
		if (word[i])
			j--;
		new_word = ft_calloc(sizeof(char), j + 1);
		ft_memcpy(new_word, word, j);
		ft_printf("test : %s\n", new_word);
		ptr = get_env(new_word, head);
		if (ptr)
		{
			ret = calloc(sizeof(char), ft_strlen(ptr->value) + 1);
			ft_memcpy(ret, ptr->value, ft_strlen(ptr->value));
		}
		else
		{
			ft_printf("env var not found :(\n");
			ret = NULL;
		}
	}
	ft_printf("ret : %s\n", ret);
	return (ret);
}


