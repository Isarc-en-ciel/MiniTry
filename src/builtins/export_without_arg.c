/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_without_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:51:41 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/31 11:25:50 by csteylae         ###   ########.fr       */
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

void	export_without_arg(t_env_list **head, t_command *cmd)
{
	t_env_list	*tmp;
	int			fd;

	*head = ft_alpha_sort(*head);
	tmp = *head;
	fd = STDOUT_FILENO;
	if (cmd->fd_out != NO_REDIR)
		fd = cmd->fd_out;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->key, fd);
		if (tmp->value)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd(tmp->value, fd);
		}
		ft_putstr_fd("\n", fd);
		tmp = tmp->next;
	}
	destroy_lst(head);
}
