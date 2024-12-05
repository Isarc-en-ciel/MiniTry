/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/05 16:37:34 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* The return status is zero unless an invalid option is supplied, one of the 
names is not a valid shell variable name, or -f is supplied with a name that is not a shell function. 
*/


static bool	is_less_than(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (!ft_strncmp(s1, s2, i))
		i++;
	if (s1[i] < s2[i])
		return (true); //s1 is less than s2
	if (!s1[i] && s2[i])
		return (true); // s1 < s2
	else if (s1[i] && !s2[i])
		return (false);
	return (false) // if s1[i] > s2[i]
}

static void	ft_alpha_sort(t_env_list *head)
{
	t_env_list	*tmp;
	t_env_list	*sorted_list;
	t_env_list	*new;
	int			len;
	char	*smallest;
	int		i = 0;

	sorted_list = new_env_list(head->key, head->value);
	len = get_list_size(head);
	while (i != len)
	{
		while (tmp->next)
		{
			if (is_less_than(tmp->key, sorted_list->next))
			{
				new =  new_env_list(tmp->key, tmp->value);
				if (!new)
				{
					//error
					return ;
				}
				ld_addfront(

			









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


