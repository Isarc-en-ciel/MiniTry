/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:50:11 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/13 18:26:17 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_n_option(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (false);
	if (arg[i] != '-')
		return (false);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	parse_option(char **cmd_arg)
{
	int	i;

	i = 1;
	while (check_n_option(cmd_arg[i]))
		i++;
	return (i);
}

int	ft_echo(char ***env, t_command *cmd, int exit_status)
{
	int		i;
	int		fd;
	bool	flag_opt;

	(void) env;
	fd = STDOUT_FILENO;
	flag_opt = false;
	if (cmd->fd_out > 0)
		fd = cmd->fd_out;
	i = parse_option(cmd->cmd);
	if (i > 1)
		flag_opt = true;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], fd);
		if (cmd->cmd[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!flag_opt)
		exit_status = write(fd, "\n", 1);
	if (exit_status < 0)
		return (FAIL);
	return (SUCCESS);
}
