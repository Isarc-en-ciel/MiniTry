/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/06 15:52:23 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static void	redirect_io(t_shell *shell, int new_fd_in, int new_fd_out)
{
	if (new_fd_in >= 0)
	{
		if (dup2(new_fd_in, STDIN_FILENO) < 0)
			exit_error(shell, "dup2");
		close(new_fd_in);
	}
	if (new_fd_out >= 0)
	{
		if (dup2(new_fd_out, STDOUT_FILENO) < 0)
			exit_error(shell, "dup2");
	}
}

static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int fd_prev)
{
	int	first_cmd;
	int	last_cmd;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;

	if (i == first_cmd)
	{
		close(pipe_fd[READ_FROM]);
		redirect_io(shell, fd_prev, pipe_fd[WRITE_TO]);
	}
	else if (i == last_cmd)
	{
		close(pipe_fd[WRITE_TO]);
		redirect_io(shell, fd_prev, STDOUT_FILENO);
	}
	else
	{
		close(pipe_fd[READ_FROM]);
		redirect_io(shell, fd_prev, pipe_fd[WRITE_TO]);
	}
}

static void wait_children(pid_t *child_pid, int child_nb)
{
	int	i;

	i = 0;
	while (i != child_nb)
	{
		wait(NULL);
		i++;
	}
	free(child_pid);
	child_pid = NULL;
}

void	exec_pipeline(t_shell *shell)
{
	int	i;
	int	pipe_fd[2];
	pid_t *child_pid;
	int	prev_fd;

	i = 0;
	child_pid = malloc(sizeof(*child_pid) * shell->tab_size);
	if (!child_pid)
		exit_error(shell, "malloc");
	prev_fd = 0; // check if REDIR_INprev_fd = open_files();
	while (i != shell->tab_size) //while command arent executed
	{
		//perform_redirections_files()
		if (pipe(pipe_fd) < 0)
			exit_error(shell, "pipe");
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			exit_error(shell, "fork");
		else if (child_pid[i] == 0)
		{
			redirect_pipeline(shell, i, pipe_fd, prev_fd);
			exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
		prev_fd = pipe_fd[READ_FROM];
		i++;
	}
	close(prev_fd);
	wait_children(child_pid, i);
}
