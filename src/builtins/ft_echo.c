/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:50:11 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/02 16:01:26 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* the output wont be the same whether we use write() syscall or our ft_putstr_fd */

bool	check_n_option(char *arg)
{
	int	i;

	if (!arg)
		return (false);
	i = 0;
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

int	ft_echo(char ***env, t_command *cmd)
{
	int	i;
	int	fd;
	int	flag_opt;

	(void) env;
	fd = STDOUT_FILENO;
	flag_opt = 0;
	if (cmd->fd_out > 0)
		fd = cmd->fd_out;
	i = 1;
	if (check_n_option(cmd->cmd[i]))
		flag_opt = 1;
//	if (flag_opt == 0)
//		write(fd, "\n", 1);
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
