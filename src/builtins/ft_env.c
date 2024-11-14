/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:03:21 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/14 22:51:04 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//env is not a builtin !
int	ft_env(char ***env, t_command *cmd)
{
	int			i;
	char		**env_b;
	char		*_env;
	t_env_list	*head;

	if (!env || !*env || !**env)
	{
		cmd->error = set_error(cmd->cmd[0], NO_ENV);
		return (0);
	}
	i = 0;
	_env = ft_strdup("usr/bin/env");
	if (!_env)
	{
		//free somth
		//return and should set error
		//perror maybe
	}
	head = array_to_list(*env);
	if (!head)
	{
		//do somthg
	}
	if (!env_modify_value("_", _env, &head))
	{
		ft_printf("key not found :((((((((((\n");
	}
	*env = list_to_array(&head);
	env_b = *env;
	while (env_b[i])
	{
		ft_printf("%s\n", env_b[i]);
		i++;
	}
	return (0);
}
