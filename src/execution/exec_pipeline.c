/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/07 12:24:25 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_child(t_shell *sh, int pipe_fd[2], int prev_fd, int i)
{
	int	exit_status;

	sh->exit_status = sh->tab[i].error.code;
	exit_status = sh->exit_status;
	close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
	free_shell(sh);
	exit(exit_status);
}

/*
static void	critical_exec_error(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	int	n;

	n = 0;
	while (n != i)
	{
		kill(sh->child_pid[n], SIGTERM);
		n++;
	}
	sh->exit_status = wait_children(sh, sh->child_pid, i);
	close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
	free_shell(sh);
	exit(EXIT_FAILURE);
}
*/
static void	launch_cmd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;
	t_builtin	*builtin;

	cmd = &sh->tab[i];
	builtin = find_builtin(sh, cmd);
	if (cmd->error.code != SUCCESS)
		exit_child(sh, pipe_fd, prev_fd, i);
	if (configure_pipeline(sh, i, pipe_fd, prev_fd) == FAIL)
		exit_child(sh, pipe_fd, prev_fd, i);
	if (builtin)
		exec_builtin(builtin, cmd, sh);
	else
		exec_external_command(sh, i);
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
	int		pipe_fd[2];
	int		prev_fd;
	int		i;

	prev_fd = NO_REDIR;
	i = 0;
	if (is_only_one_builtin(sh, i))
		return ;
	if (!init_child_pid(sh))
		return ;
	while (i != sh->tab_size)
	{
		perform_redirection(sh, &sh->tab[i]);
		init_pipeline(sh, i, pipe_fd, prev_fd);
		if (sh->child_pid[i] == CHILD_PROCESS)
			launch_cmd(sh, i, pipe_fd, prev_fd);
		prev_fd = get_prev_fd(sh, i, pipe_fd, prev_fd);
		i++;
	}
	terminate_pipeline(sh, i, prev_fd);
}
