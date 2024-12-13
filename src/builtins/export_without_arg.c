/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:51:41 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/13 18:28:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_less_than(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] < s2[i])
		return (true);
	else if (!s1[i] && s2[i])
		return (true);
	else if (s1[i] && ! s2[i])
		return (false);
	return (false);
}

static void	ft_swap_list(t_env_list *a, t_env_list *b)
{
	char	*key;
	char	*value;

	key = a->key;
	value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = key;
	b->value = value;
}

static t_env_list	*ft_alpha_sort(t_env_list *head)
{
	t_env_list	*tmp;
	t_env_list	*iterator;

	tmp = head->next;
	iterator = head;
	while (iterator->next)
	{
		while (tmp)
		{
			if (is_less_than(tmp->key, iterator->key))
			{
				ft_swap_list(iterator, tmp);
			}
			tmp = tmp->next;
		}
		iterator = iterator->next;
		tmp = iterator;
	}
	return (head);
}

void	print_all_env_var(t_env_list **head)
{
	t_env_list	*tmp;

	*head = ft_alpha_sort(*head);
	tmp = *head;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->is_init == false)
			ft_printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
	destroy_lst(head);
}
