/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:14:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/03 13:35:48 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_validity(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] && !ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(char ***env, t_command *cmd, int exit_status)
{
	int	status;

	(void)env;
	status = 0;
	if (cmd->cmd[1] != NULL)
	{
		if (!check_validity(cmd->cmd[1]))
		{
			return (builtin_error(cmd, "exit", BAD_ARG, NULL));
		}
		status = ft_atoi(cmd->cmd[1]);
		if (status > 255)
			status = status % 256;
	}
	else
		status = exit_status;
	exit(status);
}
