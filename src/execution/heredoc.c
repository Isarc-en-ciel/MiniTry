/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:09 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/19 13:54:06 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * If the redirection is a heredoc, we need firstly to create the tmp file. If it
 * already exist, we remove it with unlink(). Then we call fork() syscall and
 * write in the child the content of our heredoc. Once the delimiter is found, 
 * we close our file descriptor and change the name of the filename
 * in redir->filename with our path to that file
 * so we will be able to use it as any other file in the function open_file()
 *
 */
#include "../../inc/minishell.h"

void	write_heredoc(t_shell *shell, int fd_hd, t_redirect *redir)
{
	char	*line;
	char	*hd_del;

	line = NULL;
	hd_del = redir->hd_delimiter;
	while (1)
	{
		write(STDIN_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit_error(shell, "get_next_line\n");
		if (ft_strncmp(hd_del, line, ft_strlen(hd_del)) == 0
			&& line[ft_strlen(hd_del)] == '\n')
			break ;
		write(fd_hd, line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	free(line);
	line = NULL;
	close(fd_hd);
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

void	get_hd_filename(t_command *cmd, t_redirect *redir)
{
	free(redir->filename);
	redir->filename = ft_strdup(HEREDOC_FILE);
	if (!redir->filename)
		cmd->error = set_error("malloc", MALLOC);
}

void	create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redir)
{
	int		heredoc;
	int		pid;

	if (access(HEREDOC_FILE, F_OK) == 0)
		unlink(HEREDOC_FILE);
	heredoc = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (heredoc == -1)
	{
		cmd->error = set_error("heredoc", OPEN_FILE);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		cmd->error = set_error("fork", SYSCALL_ERROR);
		return ;
	}
	else if (pid == 0)
		write_heredoc(shell, heredoc, redir);
	waitpid(pid, NULL, 0);
	close(heredoc);
	get_hd_filename(cmd, redir);
}
