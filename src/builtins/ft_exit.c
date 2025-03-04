/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:14:42 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/04 16:20:56 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_arg_error(char *str)
{
	ft_putstr_fd("minishell: exit ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static bool	check_validity(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+')
			i++;
		if (str[i] && !ft_isdigit(str[i]))
		{
			exit_arg_error(str);
			return (false);
		}
		i++;
	}
	return (true);
}

static int	get_exit_arg(char *str)
{
	long long	status;

	if (!check_validity(str))
	{
		return (SYNTAX_ERROR);
	}
	status = ft_atoi(str);
	if (status >= LLONG_MAX)
	{
		exit_arg_error(str);
		return (SYNTAX_ERROR);
	}
	if (status > 255)
		status = status % 256;
	return (status);
}

int	ft_exit(t_shell *sh, t_command *cmd)
{
	int	status;

	status = 0;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		if (!check_validity(cmd->cmd[1]) || !check_validity(cmd->cmd[2]))
			exit(SYNTAX_ERROR);
		else
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			exit(FAIL);
		}
	}
	if (cmd->cmd[1] != NULL)
		status = get_exit_arg(cmd->cmd[1]);
	else
		status = sh->exit_status;
	if (sh->tab_size == 1)
		ft_printf("exit\n");
	free_shell(sh);
	exit(status);
}
