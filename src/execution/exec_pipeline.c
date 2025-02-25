/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/25 15:07:18 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_child(t_shell *sh, int pipe_fd[2], int prev_fd, int i)
{
	int	exit_status;

	sh->exit_status = sh->tab[i].error.code;
	exit_status = sh->tab[i].error.code;
	close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
	free_shell(sh);
	exit(exit_status);
}

static void	launch_cmd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	int			status;
	t_command	*cmd;
	t_builtin	*builtin;

	status = SUCCESS;
	cmd = &sh->tab[i];
	builtin = find_builtin(sh, cmd);
	perform_redirection(sh, &sh->tab[i]);
	if (is_error_with_cmd(cmd))
		exit_child(sh, pipe_fd, prev_fd, i);
	status = configure_pipeline(sh, i, pipe_fd, prev_fd);
	if (status == SUCCESS)
	{
		if (builtin)
			exec_builtin(builtin, cmd, sh);
		else
			exec_external_cmd(sh, i);
	}
	exit_child(sh, pipe_fd, prev_fd, i);
}

static int	get_prev_fd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;

	cmd = &sh->tab[i];
	if (close_fd(&pipe_fd[WRITE_TO]) == FAIL || close_fd(&prev_fd) == FAIL)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		cmd->error = set_error(NULL, SYSCALL_ERROR);
		return (NO_REDIR);
	}
	if (cmd->fd_out != NO_REDIR)
		close_fd(&pipe_fd[READ_FROM]);
	return (pipe_fd[READ_FROM]);
}

void	exec_pipeline(t_shell *sh)
{
	int	pipe_fd[2];
	int	prev_fd;
	int	i;

	prev_fd = NO_REDIR;
	i = 0;
	while (i != sh->tab_size)
	{
		init_pipeline(sh, i, pipe_fd, prev_fd);
		sh->child_pid[i] = fork();
		if (sh->child_pid[i] < 0)
			exit_error(sh, "fork");
		if (sh->child_pid[i] == CHILD_PROCESS)
		{
			set_signal_in_child(sh, i, pipe_fd, prev_fd);
			launch_cmd(sh, i, pipe_fd, prev_fd);
		}
		prev_fd = get_prev_fd(sh, i, pipe_fd, prev_fd);
		i++;
	}
	terminate_pipeline(sh, i, prev_fd);
}
