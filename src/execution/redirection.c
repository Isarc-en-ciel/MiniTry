/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/27 13:10:16 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	redirect_io(t_shell *shell, int new_fd_in, int new_fd_out)
{
	if (new_fd_in >= 0)
	{
		if (dup2(new_fd_in, STDIN_FILENO) < 0)
			exit_error(shell, "dup2");
	}
	if (new_fd_out >= 0)
	{
		if (dup2(new_fd_out, STDOUT_FILENO) < 0)
			exit_error(shell, "dup2");
	}
}

int	open_file(t_shell *shell, int prev_fd, t_redirect redir, int flags)
{
	int	fd;

	fd = 0;
	if (prev_fd > 2)
		close(prev_fd);
	if (flags & O_CREAT)
		fd = open(redir.filename, flags, 0644);
	else
		fd = open(redir.filename, flags);
	if (fd < 0)
		exit_error(shell, "open");
	return (fd);
}

static int	get_flags(int redir_type)
{
	int	flags;

	flags = 0;
	if (redir_type == REDIR_HEREDOC)
	{
		//flags = heredoc flags ou jsp quoi omg :(((((((((((
	}
	else if (redir_type == REDIR_IN)
		flags = O_RDONLY;
	else if (redir_type == REDIR_OUT)
		flags = O_WRONLY | O_TRUNC | O_CREAT;
	else if (redir_type == REDIR_APP)
		flags = O_WRONLY | O_APPEND | O_CREAT;
	return (flags);
}

void	perform_redirection(t_shell *shell, t_command *cmd)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	if (!cmd->redirection.size)
		return ;
	while (i != cmd->redirection.size)
	{
		flags = get_flags(cmd->redirection.array[i].type);
		if (cmd->redirection.array[i].type == REDIR_HEREDOC)
		{
			//do heredoc
		}
		else if (cmd->redirection.array[i].type == REDIR_IN)
			cmd->fd_in = open_file(shell, cmd->fd_in, cmd->redirection.array[i], flags);
		else
			cmd->fd_out = open_file(shell, cmd->fd_out, cmd->redirection.array[i], flags);
		i++;
	}
	redirect_io(shell, cmd->fd_in, cmd->fd_out);
}
