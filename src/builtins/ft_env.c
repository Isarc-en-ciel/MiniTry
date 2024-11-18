/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:03:21 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 16:19:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char ***env, t_command *cmd)
{
//	int			i;
//	char		**env_b;
//	t_env_list	*head;

	if (!env || !*env || !**env)
		return (0);
	(void)cmd;
//	i = 0;
//	//head = init_list(*env, cmd);
//	if (cmd->error.code != OK)
//		return (-1);
//
//
//	//replace value
//	//list_to_array
//	//return
//
//
//	
//	*env = list_to_array(&head);
//	env_b = *env;
//	while (env_b[i])
//	{
//		ft_printf("%s\n", env_b[i]);
//		i++;
//	}
	return (0);
}
