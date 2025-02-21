/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:49:43 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 11:20:43 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* the function perform_redirection will iterate troughout the array 
 * of redirection. It will open the file that redirect the stdin and stdout
 * of the cmd and keep it in cmd->fd_in and cmd->fd_out. 
 * For that, we begin to check which type of redirection it
 * and give the appropriate flags that we will pass to open() syscall
 * before opening the file, the function check for the appropriate type if the
 * permission are required with access() and eventually close the previous 
 * fd open if its > 2
 */
#include "../../inc/minishell.h"

void	redirect_io(t_shell *shell, int new_fd_in, int new_fd_out)
{
	if (new_fd_in > NO_REDIR)
	{
		if (dup2(new_fd_in, STDIN_FILENO) < 0)
			exit_error(shell, "dup2");
	}
	if (new_fd_out > NO_REDIR)
	{
		if (dup2(new_fd_out, STDOUT_FILENO) < 0)
			exit_error(shell, "dup2");
	}
}

int	open_file(t_command *cmd, int prev_fd, t_redirect redir, int flags)
{
	int	fd;

	fd = 0;
	if (prev_fd > 2)
	{
		if (close_fd(&prev_fd) == FAIL)
		{
			cmd->error = set_error(NULL, SYSCALL_ERROR);
			return (NO_REDIR);
		}
	}
	if (flags & O_CREAT)
		fd = open(redir.filename, flags, 0644);
	else
		fd = open(redir.filename, flags);
	if (fd < 0)
		cmd->error = set_error(redir.filename, FAIL);
	return (fd);
}

static int	get_flags(t_shell *sh, t_command *cmd, t_redirect *redir, int type)
{
	int	flags;

	flags = 0;
	if (type == REDIR_HEREDOC)
	{
		create_heredoc(sh, cmd, redir);
		flags = O_RDONLY;
	}
	else if (type == REDIR_IN)
		flags = O_RDONLY;
	else if (type == REDIR_OUT)
		flags = O_WRONLY | O_TRUNC | O_CREAT;
	else if (type == REDIR_APP)
		flags = O_WRONLY | O_APPEND | O_CREAT;
	return (flags);
}

void	perform_redirection(t_shell *shell, t_command *cmd)
{
	int				i;
	int				flags;
	t_redir_array	*redir;

	i = 0;
	flags = 0;
	redir = &cmd->redirection;
	if (!redir->size)
		return ;
	while (i != redir->size)
	{
		flags = get_flags(shell, cmd, &redir->array[i], redir->array[i].type);
		if (cmd->error.code != SUCCESS)
			return ;
		if (redir->array[i].type == REDIR_HEREDOC)
			cmd->fd_in = open_file(cmd, cmd->fd_in, redir->array[i], flags);
		else if (redir->array[i].type == REDIR_IN)
			cmd->fd_in = open_file(cmd, cmd->fd_in, redir->array[i], flags);
		else
			cmd->fd_out = open_file(cmd, cmd->fd_out, redir->array[i], flags);
		if (cmd->error.code != SUCCESS)
			return ;
		i++;
	}
}
