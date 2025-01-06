/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:45:52 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/06 13:15:33 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	init_child_pid(t_shell *sh)
{
	sh->child_pid = malloc(sizeof(sh->child_pid) * sh->tab_size);
	if (!sh->child_pid)
	{
		perror("malloc");
		return (false);
	}
	return (true);
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
	if (pipe(pipe_fd) < 0)
	{
		sh->tab[i].error = set_error("pipe", SYSCALL_ERROR);
		return (false);
	}
	return (true);
}

bool	init_pipeline(t_shell *sh, int i, int pipe_fd[2])
{
	if (!init_pipe(sh, i, sh->tab_size, pipe_fd))
	{
		return (false);
	}
	perform_redirection(sh, &sh->tab[i]);
	//do not fork a child process if a prb occur while trying 
	// to open a file ? but a prb when wait the ? so fork and close ? disgutinf idea
	sh->child_pid[i] = fork();
	if (sh->child_pid[i] < 0)
	{
		sh->tab[i].error = set_error("fork", SYSCALL_ERROR);
		return (false);
	}
	if (sh->child_pid[i] == CHILD_PROCESS)
	{
		if (sh->tab[i].error.code != OK) //aka an error occurs when attempting to open a file
			exit_error(sh, NULL);
	}
	return (true);
}
