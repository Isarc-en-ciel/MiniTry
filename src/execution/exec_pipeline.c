/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/27 17:08:06 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int fd_prev)
{
	int	first_cmd;
	int	last_cmd;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;
	if (i == first_cmd)
	{
		close(pipe_fd[READ_FROM]);
		if (shell->tab[i].fd_out == STDOUT_FILENO)
			redirect_io(shell, shell->tab[i].fd_in, pipe_fd[WRITE_TO]);
	}
	else if (i == last_cmd)
	{
		close(pipe_fd[WRITE_TO]);
		if (shell->tab[i].fd_in == STDIN_FILENO)
			redirect_io(shell, fd_prev, shell->tab[i].fd_out);
	}
	else
	{
		close(pipe_fd[READ_FROM]);
		fd_prev = shell->tab[i].fd_in;
		if (shell->tab[i].fd_out == STDOUT_FILENO)
			redirect_io(shell, fd_prev, pipe_fd[WRITE_TO]);
	}
}

static void wait_children(t_shell *shell, pid_t *child_pid, int child_nb)
{
	int	i;

	i = 0;
	while (i != child_nb)
	{
		wait(&shell->exit_status);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
		else if (WIFSIGNALED(shell->exit_status))
			shell->exit_status = WTERMSIG(shell->exit_status);
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
		if (pipe(pipe_fd) < 0)
			exit_error(shell, "pipe");
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			exit_error(shell, "fork");
		else if (child_pid[i] == 0)
		{
			perform_redirection(shell, &shell->tab[i]);
			redirect_pipeline(shell, i, pipe_fd, prev_fd);
			exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
		if (i != 0)
			close(prev_fd);
		prev_fd = pipe_fd[READ_FROM];
		i++;
	}
	wait_children(shell, child_pid, i);
	close(prev_fd);
}
