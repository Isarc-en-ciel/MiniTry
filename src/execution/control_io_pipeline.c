/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_io_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:04:23 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/21 17:40:08 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int prev_fd)
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
		if (in == NO_REDIR)
			in = STDIN_FILENO;
		if (out != NO_REDIR)
			close(pipe_fd[WRITE_TO]);
		else
			out = pipe_fd[WRITE_TO];
	}
	else if (i == last_cmd)
	{
		//no pipe
		if (in != NO_REDIR)
			close(prev_fd);
		else
			in = prev_fd;
		if (out == NO_REDIR)
			out = STDOUT_FILENO;
	}
	else
	{
		//in the middle of the pipe
		close(pipe_fd[READ_FROM]);
		if (in != NO_REDIR)
		{
			close(prev_fd);
		}
		else if (in == NO_REDIR && prev_fd != NO_REDIR)
		{
			in = prev_fd;
		}
		else if (in == NO_REDIR && prev_fd == NO_REDIR)
		{
			in = STDIN_FILENO;
		}
		if (out != NO_REDIR)
		{
			close(pipe_fd[WRITE_TO]);
		}
		else if (out == NO_REDIR)
		{
			out = pipe_fd[WRITE_TO];
		}
	}
	redirect_io(shell, in, out);
}

/*
void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int prev_fd)
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

*/
