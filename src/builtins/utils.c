/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:11:33 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 15:42:01 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_list	*init_list(char **env, t_command *cmd)
{
	t_env_list	*head;

	head = array_to_list(env);
	if (!head)
		cmd->error = set_error("malloc", MALLOC);
	return (head);
}

void	replace_env(t_env_list **head, char *key, char *value, t_command *cmd)
{
	t_env_list	*new;
	t_env_list	*tmp;

	new = new_env_list(key, value);
	if (!new)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	tmp = get_env(key, *head);



}
	

//char	**replace_env()
//{
//}
//

