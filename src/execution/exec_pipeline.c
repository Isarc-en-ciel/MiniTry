/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/14 16:41:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

/*The output of each command in the pipeline is connected via a pipe to the input of the next command. 
That is, each command reads the previous command’s output. 
This connection is performed before any redirections specified by command1. 
*/
static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int *prev_fd)
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
		if (out == NO_REDIR)
			out = pipe_fd[WRITE_TO];
		else
			close(pipe_fd[WRITE_TO]);
	}
	else if (i == last_cmd)
	{
		if (in == NO_REDIR && prev_fd >= 0)
			in = *prev_fd;
		else
			close(*prev_fd);
	}
	else //if we are in the middle of pipeline
	{
		if (in == NO_REDIR)
			in = *prev_fd;
		else 
			close(*prev_fd);
		if (out == NO_REDIR)
			out = pipe_fd[WRITE_TO];
		else
			close(pipe_fd[WRITE_TO]);
	}
	shell->tab[i].fd_in = in;
	shell->tab[i].fd_out = out;
	redirect_io(shell, in, out);
}
//static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int *prev_fd)
//{
//	int	first_cmd;
//	int	last_cmd;
//	int	in;
//	int	out;
//
//	first_cmd = 0;
//	last_cmd = shell->tab_size - 1;
//	in = shell->tab[i].fd_in;
//	out = shell->tab[i].fd_out;
//	if (i == first_cmd)
//	{
//		close(pipe_fd[READ_FROM]);
//		if (shell->tab[i].fd_out == STDOUT_FILENO)
//			out = pipe_fd[WRITE_TO];
//	}
//	else if (i == last_cmd)
//	{
//		if (pipe_fd[WRITE_TO] > 2)
//			close(pipe_fd[WRITE_TO]);
//		if (shell->tab[i].fd_in == STDIN_FILENO && *prev_fd >= 0)
//			in = *prev_fd;
//	}
//	else
//	{
//		if (pipe_fd[READ_FROM] > 2)
//			close(pipe_fd[READ_FROM]);
//		if (shell->tab[i].fd_in == STDIN_FILENO)
//			in = *prev_fd;
//		if (shell->tab[i].fd_out == STDOUT_FILENO)
//			out = pipe_fd[WRITE_TO];
//	}
//	shell->tab[i].fd_in = in;
//	shell->tab[i].fd_out = out;
//	redirect_io(shell, in, out);
//}

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

void	error_pipeline(t_shell *shell, int pipe_fd[2], int prev_fd)
{
	//should free also child_pid 
	if (prev_fd > 2)
		close(prev_fd);
	if (pipe_fd[READ_FROM] > 2)
		close(pipe_fd[READ_FROM]);
	if (pipe_fd[WRITE_TO] > 2)
		close(pipe_fd[WRITE_TO]);
	exit_error(shell, "pipe");
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
	prev_fd = -1;
	while (i != shell->tab_size) 
	{
		pipe_fd[READ_FROM] = -1;
		pipe_fd[WRITE_TO] = -1;
		if (i != shell->tab_size - 1)
		{
			if (pipe(pipe_fd) == -1)
				error_pipeline(shell, pipe_fd, prev_fd);
		}
		perform_redirection(shell, &shell->tab[i]);
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			exit_error(shell, "fork");
		else if (child_pid[i] == 0)
		{
			close(pipe_fd[READ_FROM]);
			redirect_pipeline(shell, i, pipe_fd, &prev_fd);
			exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
		if (i != 0 && prev_fd > 2)
			close(prev_fd);
		if (shell->tab[i].fd_out != NO_REDIR)
		{
			close(pipe_fd[READ_FROM]);
			prev_fd = NO_REDIR;
		}
		else
			prev_fd = pipe_fd[READ_FROM];
		i++;
	}
	wait_children(shell, child_pid, i);
	if (prev_fd > 2)
		close(prev_fd);
//	delete_heredoc_file(&shell->tab[i]);
}

//void	exec_pipeline(t_shell *shell)
//{
//	int		i;
//	int		pipe_fd[2];
//	pid_t	*child_pid;
//	int		prev_fd;
//
//	i = 0;
//	child_pid = malloc(sizeof(*child_pid) * shell->tab_size);
//	if (!child_pid)
//		exit_error(shell, "malloc");
//	prev_fd = -1;
//	while (i != shell->tab_size) 
//	{
//		if (pipe(pipe_fd) < 0)
//			exit_error(shell, "pipe");
//		perform_redirection(shell, &shell->tab[i]);
//		child_pid[i] = fork();
//		if (child_pid[i] < 0)
//			exit_error(shell, "fork");
//		else if (child_pid[i] == 0)
//		{
//			redirect_pipeline(shell, i, pipe_fd, &prev_fd);
//			exec_command(shell, i);
//		}
//		close(pipe_fd[WRITE_TO]);
//		if (i != 0 && prev_fd > 2)
//			close(prev_fd);
//		prev_fd = pipe_fd[READ_FROM];
//		i++;
//	}
//	wait_children(shell, child_pid, i);
//	if (shell->tab[i].error.code == OPEN_FILE)
//		return (error_pipeline(pipe_fd, prev_fd));
//	if (prev_fd > 2)
//		close(prev_fd);
////	delete_heredoc_file(&shell->tab[i]);
//}
