/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/26 12:40:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static void	open_file(t_shell *shell, t_command *cmd, t_redirect redir)
{
	if (redir.type == REDIR_HEREDOC)
	{
		//perform_heredoc()
	}
	else if (redir.type == REDIR_IN)
	{
		close(cmd->fd_in);
		cmd->fd_in = open(redir.filename, O_RDONLY);
		if (cmd->fd_in < 0)
			exit_error(shell, "open");
	}
	else if (redir.type == REDIR_OUT)
	{	
		close(cmd->fd_out);
		cmd->fd_out = open(redir.filename, O_WRONLY | O_TRUNC, O_CREAT, 0644); 
		if (cmd->fd_out < 0)
			exit_error(shell, "open");
	}
	else if (redir.type == REDIR_APP)
	{
		close(cmd->fd_out);
		cmd->fd_out = open(redir.filename, O_WRONLY | O_APPEND, O_CREAT, 0644);
		if (cmd->fd_out < 0)
			exit_error(shell, "open");
	}
}

void	perform_redirection(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	if (!cmd->redirection.array)
		return ;
	while (i != cmd->redirection.size)
	{
		open_file(shell, cmd, cmd->redirection.array[i]);
		i++;
	}
	if (dup2(STDIN_FILENO, cmd->fd_in) < 0)
		exit_error(shell, "dup2");
	if (dup2(STDOUT_FILENO, cmd->fd_out) < 0)
		exit_error(shell, "dup2");
}
