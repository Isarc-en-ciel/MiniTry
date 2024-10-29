/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:19:23 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/29 17:28:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	ft_pwd(char ***env, char **args)
{
	t_env_list	*head;
	t_env_list	*pwd;

	if (args[1])
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
	pwd = find_node("PWD", head);
	ft_printf("%s\n", pwd->value);
	if (!pwd)
	{
		//return exit status pwd not found
	}
	destroy_lst(&head);
	return (0);
}
