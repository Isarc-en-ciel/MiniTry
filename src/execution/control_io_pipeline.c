/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_io_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:04:23 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/30 12:47:17 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	handle_first_cmd(int *in, int *out, int pipe_fd[2])
{
	if (close_fd(&pipe_fd[READ_FROM]) == FAIL)
		return (FAIL);
	if (*in == NO_REDIR)
		*in = STDIN_FILENO;
	if (*out != NO_REDIR)
	{
		if (close_fd(&pipe_fd[WRITE_TO]) == FAIL)
			return (FAIL);
	}
	else
		*out = pipe_fd[WRITE_TO];
	return (SUCCESS);
}

static int	handle_last_cmd(int *in, int *out, int prev_fd)
{
	if (*in != NO_REDIR)
	{
		if (close_fd(&prev_fd) == FAIL)
			return (FAIL);
	}
	else
		*in = prev_fd;
	if (*out == NO_REDIR)
		*out = STDOUT_FILENO;
	return (SUCCESS);
}

static int	handle_middle_cmd(int *in, int *out, int pipe_fd[2], int prev_fd)
{
	if (close_fd(&pipe_fd[READ_FROM]) == FAIL)
		return (FAIL);
	if (*in != NO_REDIR)
	{
		if (close_fd(&prev_fd) == FAIL)
			return (FAIL);
	}
	else if (*in == NO_REDIR && prev_fd != NO_REDIR)
		*in = prev_fd;
	else if (*in == NO_REDIR && prev_fd == NO_REDIR)
		*in = STDIN_FILENO;
	if (*out != NO_REDIR)
	{
		if (close_fd(&pipe_fd[WRITE_TO]) == FAIL)
			return (FAIL);
	}
	else if (*out == NO_REDIR)
		*out = pipe_fd[WRITE_TO];
	return (SUCCESS);
}

int	configure_pipeline(t_shell *shell, int i, int pipe_fd[2], int prev_fd)
{
	int	first_cmd;
	int	last_cmd;
	int	in;
	int	out;
	int	flag;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;
	in = shell->tab[i].fd_in;
	out = shell->tab[i].fd_out;
	if (i == first_cmd)
		flag = handle_first_cmd(&in, &out, pipe_fd);
	else if (i == last_cmd)
		flag = handle_last_cmd(&in, &out, prev_fd);
	else
		flag = handle_middle_cmd(&in, &out, pipe_fd, prev_fd);
	if (flag == FAIL)
		return (FAIL);
	redirect_io(shell, in, out);
	return (SUCCESS);
}
