/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:45:52 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 12:55:06 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_child_pid(t_shell *sh)
{
	sh->child_pid = malloc(sizeof(sh->child_pid) * sh->tab_size);
	if (!sh->child_pid)
	{
		exit_error(sh, "malloc");
	}
}

static bool	init_pipe(t_shell *sh, int i, int tab_size, int pipe_fd[2])
{
	int	last_cmd;

	last_cmd = tab_size - 1;
	if (i == last_cmd)
	{
		pipe_fd[READ_FROM] = NO_REDIR;
		pipe_fd[WRITE_TO] = NO_REDIR;
		return (true);
	}
	else if (pipe(pipe_fd) < 0)
	{
		sh->tab[i].error = set_error("pipe", SYSCALL_ERROR);
		return (false);
	}
	return (true);
}

void	init_pipeline(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	pipe_fd[READ_FROM] = NO_REDIR;
	pipe_fd[WRITE_TO] = NO_REDIR;
	if (!init_pipe(sh, i, sh->tab_size, pipe_fd))
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		exit_error(sh, NULL);
	}
}
