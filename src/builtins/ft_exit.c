/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:14:42 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/07 13:29:05 by csteylae         ###   ########.fr       */
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
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", str);
			return (false);
		}
		i++;
	}
	return (true);
}

int	ft_exit(t_shell *sh, t_command *cmd)
{
	int	status;

	status = 0;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDOUT_FILENO);
		return (FAIL);
	}
	if (cmd->cmd[1] != NULL)
	{
		if (!check_validity(cmd->cmd[1]))
			status = 255;
		else
		{
			status = ft_atoi(cmd->cmd[1]);
			if (status > 255)
				status = status % 256;
		}
	}
	else
		status = sh->exit_status;
	if (sh->tab_size == 1)
		ft_printf("exit\n");
	exit(status);
}
