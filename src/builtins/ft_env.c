/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:03:21 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/30 12:10:25 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	ft_env(char ***env, t_command *cmd)
{
	int			i;
	char		**env_b;
	char		*_env;
	t_env_list	*head;

	(void)cmd;
	if (!env || !*env || !**env)
		return (0);
	i = 0;
	env_b = *env;
	_env = ft_strdup("usr/bin/env");
	if (!_env)
	{
		//free somth
		//return and should set error
		//perror maybe
	}
	head = array_to_list(env_b);
	if (!head)
	{
		//do somthg
	}
	if (!env_modify_value("_", _env, &head))
	{
		ft_printf("key not found :((((((((((\n");
	}
	env_b = list_to_array(&head);
	while (env_b[i])
	{
		ft_printf("%s\n", env_b[i]);
		i++;
	}
	return (0);
}
