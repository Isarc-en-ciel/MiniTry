/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/06 15:03:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* The return status is zero unless an invalid option is supplied, one of the 
names is not a valid shell variable name, or -f is supplied with a name that is not a shell function. 
*/


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

static void	print_all_env_var(t_env_list *sorted_list)
{
	t_env_list	*tmp;

	tmp = sorted_list;
	while (tmp)
	{	
		if (tmp->value)
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			ft_printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
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

int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	(void)exit_status;
	int	i;

	i = 0;
	head = array_to_list(*env);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	if (!cmd->cmd[1])
	{
		head = ft_alpha_sort(head);
		print_all_env_var(head);
		destroy_lst(&head);
		return (SUCCESS);
	}
//	check_identifier_rules(cmd);

	return (SUCCESS);
}


