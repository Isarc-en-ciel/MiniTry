/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:50:11 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/03 12:12:23 by csteylae         ###   ########.fr       */
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

int	ft_echo(char ***env, t_command *cmd, int exit_status)
{
	int	i;
	int	fd;
	int	flag_opt;

	(void) env;
	(void) exit_status;
	fd = STDOUT_FILENO;
	flag_opt = 0;
	i = 1;
	if (cmd->fd_out > 0)
		fd = cmd->fd_out;
	if (check_n_option(cmd->cmd[i]))
		flag_opt = 1;
	while (check_n_option(cmd->cmd[i]))
		i++;
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], fd);
		i++;
	}
	if (flag_opt == 0)
		write(fd, "\n", 1);
	return (SUCCESS);
}
