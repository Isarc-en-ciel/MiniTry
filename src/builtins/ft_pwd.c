/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:23 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 16:01:54 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(char ***env, t_command *cmd)
{
	t_env_list	*head;
	t_env_list	*pwd;

	if (cmd->cmd[1])
	{
		// not good 
		// idk what to do
		// go ask to people how to manage it
	}
	head = array_to_list(*env);
	if (!env)
	{
		// perror("malloc")
		// return
	}
	pwd = get_env("PWD", head);
	ft_printf("%s\n", pwd->value);
	if (!pwd)
	{
		//return exit status pwd not found
	}
	destroy_lst(&head);
	return (0);
}
