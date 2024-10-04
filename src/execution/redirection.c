/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:34:12 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/04 21:13:32 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/04 20:33:27 by csteylae         ###   ########.fr       */
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

int	open_file(t_command *cmd, int prev_fd, t_redirect redir, int flags)
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
		cmd->error = set_error(redir.filename, OPEN_FILE);
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

void	exec_heredoc(t_shell *shell, t_command *cmd, t_redirect redir)
{
	int	pipe_heredoc[2];
	int	pid;
	char *line;

	line = NULL;
	ft_printf("hd del : %s\n", redir.hd_delimiter);
	if (pipe(pipe_heredoc) < 0)
	{
		cmd->error = set_error(redir.filename, OPEN_FILE);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipe_heredoc[READ_FROM]);
		if (dup2(pipe_heredoc[WRITE_TO], STDOUT_FILENO) < 0)
		{
			close(pipe_heredoc[WRITE_TO]);
			exit_error(shell, "pipe");
		}
		while (1)
		{
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(redir.hd_delimiter, line, ft_strlen(redir.hd_delimiter)) == 0
                && line[ft_strlen(redir.hd_delimiter)] == '\n')
				break;
			write(pipe_heredoc[WRITE_TO], line, ft_strlen(line));
			free(line);
			line = NULL;
		}
		close(pipe_heredoc[WRITE_TO]);
		free(line);
		line = NULL;
		exit(EXIT_SUCCESS);
	}
	close(pipe_heredoc[WRITE_TO]);
	waitpid(pid, NULL, 0);
	cmd->fd_in = pipe_heredoc[READ_FROM];
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
			exec_heredoc(shell, cmd, cmd->redirection.array[i]);
		}
		else if (cmd->redirection.array[i].type == REDIR_IN)
			cmd->fd_in = open_file(cmd, cmd->fd_in, cmd->redirection.array[i], flags);
		else
			cmd->fd_out = open_file(cmd, cmd->fd_out, cmd->redirection.array[i], flags);
		//check if error has occured
		if (cmd->error.code == OPEN_FILE)
			return ;
		i++;
	}
	redirect_io(shell, cmd->fd_in, cmd->fd_out);
}
