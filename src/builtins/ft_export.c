/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/05 20:53:11 by csteylae         ###   ########.fr       */
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
//	ft_printf("s1 : %s, s2 : %s\n", s1, s2);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] < s2[i])
		return (true); //s1 is less than s2
	else if (!s1[i] && s2[i])
		return (true);
	else if (s1[i] && ! s2[i])
		return (false);
	return (false); // if s1[i] > s2[i]
}

static t_env_list	*ft_alpha_sort(t_env_list *head)
{
	t_env_list	*tmp;
	t_env_list	*swap;
	int			len;

	tmp = head->next;
	swap = NULL;
	len = get_list_size(head);
	while (len > 0)
	{
		while (tmp)
		{
			if (is_less_than(tmp->key, head->key))
			{
				swap = tmp;
				ft_printf("tmp->key %s, head->key :%s\n", tmp->key, head->key);
				tmp->value = head->value;
				tmp->key = head->key;
				head->value = swap->value;
				head->key = swap->key;
			}
			tmp = tmp->next;
		}
		len--;
		tmp = head->next;
	}
//	ft_printf("len : %i\n", len);
//	ft_print_list(head);
	return (head);
}


int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	(void)exit_status;

	head = array_to_list(*env);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	if (!cmd->cmd[1])
	{
		ft_alpha_sort(head);
	}
	return (SUCCESS);
}


