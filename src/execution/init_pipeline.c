/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:45:52 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/21 17:18:54 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	init_pipe(t_shell *sh, int i, int tab_size, int pipe_fd[2])
{
	int	last_cmd;

	last_cmd = tab_size - 1;
	if (i == last_cmd)
	{
		//no pipe
		pipe_fd[READ_FROM] = NO_REDIR;
		pipe_fd[WRITE_TO] = NO_REDIR;
		return (true);
	}
	if (pipe(pipe_fd) < 0)
	{
		sh->tab[i].error = set_error("pipe", SYSCALL_ERROR);
		return (false);
	}
//	ft_printf("pipe[READ] : %d, pipe[WRITE] : %d\n", pipe_fd[READ_FROM], pipe_fd[WRITE_TO]);
	return (true);
}

bool	init_pipeline(t_shell *sh, int i, int pipe_fd[2])
{
	if (!init_pipe(sh, i, sh->tab_size, pipe_fd))
	{
		return (false);
	}
	perform_redirection(sh, &sh->tab[i]);
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
