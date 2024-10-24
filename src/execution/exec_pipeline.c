/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/22 16:34:00 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

/*The output of each command in the pipeline is connected via a pipe to the input of the next command. 
That is, each command reads the previous command’s output. 
This connection is performed before any redirections specified by command1. 
*/
static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int prev_fd)
{
	int	first_cmd;
	int	last_cmd;
	int	in;
	int	out;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;
	in = shell->tab[i].fd_in;
	out = shell->tab[i].fd_out;

	if (i == first_cmd)
	{
		close(pipe_fd[READ_FROM]);
		if (shell->tab[i].fd_in != NO_REDIR)
			in = shell->tab[i].fd_in;
		else
			in = STDIN_FILENO;
		out = pipe_fd[WRITE_TO];
		if (shell->tab[i].fd_out != NO_REDIR)
		{
			close(pipe_fd[WRITE_TO]);
			out = shell->tab[i].fd_out;
		} 
	}
	else if (i == last_cmd)
	{
		//no pipe
		if (prev_fd != NO_REDIR)
			in = prev_fd;
		if (shell->tab[i].fd_in != NO_REDIR)
		{
			close(prev_fd);
			in = shell->tab[i].fd_in;
		}
		if (shell->tab[i].fd_out != NO_REDIR)
			out = shell->tab[i].fd_out;
		else
			out = STDOUT_FILENO;
	}
	else
	{
		close(pipe_fd[READ_FROM]);
		if (prev_fd > -1)
		{
			in = prev_fd;
		}
		else
			in = STDIN_FILENO;
		if (shell->tab[i].fd_in != NO_REDIR)
		{
			if (prev_fd > -1)
				close(prev_fd);
			in = shell->tab[i].fd_in;
		}
		out = pipe_fd[WRITE_TO];
		if (shell->tab[i].fd_out != NO_REDIR)
		{
			close(pipe_fd[WRITE_TO]);
			out = shell->tab[i].fd_out;
		}
	}
	redirect_io(shell, in, out);
}

static void wait_children(t_shell *shell, pid_t *child_pid, int child_nb)
{
	int	i;

	i = 0;
	(void) shell;
	while (i != child_nb)
	{
		wait(NULL);
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

void	error_pipeline(t_shell *shell, pid_t **children, int pipe_fd[2], int prev_fd)
{
	//should free also child_pid 
	if (*children)
	{
		free(*children);
		children = NULL;
	}
	if (prev_fd > 2)
		close(prev_fd);
	if (pipe_fd[READ_FROM] > 2)
		close(pipe_fd[READ_FROM]);
	if (pipe_fd[WRITE_TO] > 2)
		close(pipe_fd[WRITE_TO]);
	exit_error(shell, NULL);
}

/*The output of each command in the pipeline is connected via a pipe to the input of the next command. 
That is, each command reads the previous command’s output. 
This connection is performed before any redirections specified by command1. 
*/
void	exec_pipeline(t_shell *shell)
{
	int		i;
	int		pipe_fd[2];
	pid_t	*child_pid;
	int		prev_fd;

	i = 0;
	child_pid = malloc(sizeof(*child_pid) * shell->tab_size);
	if (!child_pid)
		exit_error(shell, "malloc");
	prev_fd = NO_REDIR;
	while (i != shell->tab_size) 
	{
		if (i != shell->tab_size - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				shell->tab[i].error = set_error("pipe", PIPE_ERROR);
				error_pipeline(shell, &child_pid,  pipe_fd, prev_fd);
			}
		}
		perform_redirection(shell, &shell->tab[i]);
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			exit_error(shell, "fork");
		else if (child_pid[i] == 0)
		{
			if (shell->tab[i].error.code != OK)
				error_pipeline(shell, &child_pid,  pipe_fd, prev_fd);
			redirect_pipeline(shell, i, pipe_fd, prev_fd);
			exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
//		if (i != 0 && prev_fd > 2)
//		{
//			close(prev_fd);
//			prev_fd = NO_REDIR;
//		}
		if (prev_fd > 2)
			close(prev_fd);
		if (i != 0 && shell->tab[i - 1].fd_out != NO_REDIR)
		{
			close(pipe_fd[READ_FROM]);
			prev_fd = LAST_PIPE_CLOSED;
		}
		else
		{
			prev_fd = pipe_fd[READ_FROM];
		}
		i++;
	}
	wait_children(shell, child_pid, i);
	if (prev_fd > 2)
		close(prev_fd);
}
