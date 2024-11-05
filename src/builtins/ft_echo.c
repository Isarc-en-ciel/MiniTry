/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:50:11 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/05 17:35:10 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
 * Suppose that arg[1] that echo will output has no more quotes, their expansion
 * is already done
 *
 * -> should manage the -n arg =>check how bash manage it
 *
 * echo with option -n
 */

bool	check_n_option(char *arg)
{
	int	i;

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

	i = 0;
	(void)env;
	if (cmd->fd_out != NO_REDIR)
		fd = cmd->fd_out;
	else
		fd = STDOUT_FILENO;
	while (check_n_option(cmd->cmd[i]))
		i++;
	if (i ==  1)
	{
		if (write(fd, "\n", 1) != 0)
			return (-1);
	}
	while (cmd->cmd[i])
	{
		ft_putstr_fd(cmd->cmd[i], fd);
		i++;
	}
	return (0);
}
