/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:09 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/03 16:47:43 by csteylae         ###   ########.fr       */
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

static void	handle_hd_expansion(char **line, int fd, t_shell *sh, t_redirect *r)
{
	char	*line_to_exp;

	line_to_exp = NULL;
	if (line && *line && ft_strchr(*line, '$') && r->hd_expansion == true)
	{
		line_to_exp = ft_calloc(ft_strlen(*line), sizeof(char));
		if (!line_to_exp)
		{
			free(line);
			close(fd);
			exit_error(sh, "ft_calloc");
		}
		ft_memcpy(line_to_exp, *line, ft_strlen(*line) - 1);
		free(*line);
		expand_var(sh, &line_to_exp);
		*line = ft_strjoin(line_to_exp, "\n", S1_MALLOC);
		if (!*line)
		{
			close(fd);
			exit_error(sh, "ft_calloc");
		}
	}
	return ;
}

static void	write_heredoc(t_shell *shell, int fd_hd, t_redirect *redir)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> "); 
		if (!line)
		{
			ft_printf("warning : heredoc terminate with eof\n");
			break ;
		}
		if (key_found(redir->hd_delimiter, line))
			break ;
		handle_hd_expansion(&line, fd_hd, shell, redir);
		write(fd_hd, line, ft_strlen(line));
		write(fd_hd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd_hd);
	free_shell(shell);
	exit(EXIT_SUCCESS);
}

static void	get_hd_filename(t_command *cmd, t_redirect *redir)
{
	free(redir->filename);
	redir->filename = ft_strdup(HEREDOC_FILE);
	if (!redir->filename)
		cmd->error = set_error("malloc", MALLOC);
}

static void	setup_sigquit_hd(t_shell *sh, int fd, t_command *cmd)
{
	struct sigaction hd_sigquit;

	ft_bzero(&hd_sigquit, sizeof(hd_sigquit));
	hd_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&hd_sigquit.sa_mask);
	hd_sigquit.sa_flags = 0;
	if (sigaction(SIGQUIT, &hd_sigquit, NULL) != SUCCESS)
	{
		cmd->error = set_error("sigaction", SYSCALL_ERROR);
		close_fd(&fd);
		exit_error(sh, NULL);
	}
}

void	create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redir)
{
	int		heredoc;
	int		pid;
	struct sigaction	old_act;

   	sigaction(SIGQUIT, NULL, &old_act);
	heredoc = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (heredoc == -1)
	{
		cmd->error = set_error("heredoc", FAIL);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		cmd->error = set_error("fork", SYSCALL_ERROR);
		return ;
	}
	if (pid == CHILD_PROCESS)
	{
		setup_sigquit_hd(shell, heredoc, cmd);
		write_heredoc(shell, heredoc, redir);
	}
	waitpid(pid, NULL, 0);
	sigaction(SIGQUIT, &old_act, NULL);
	close(heredoc);
	get_hd_filename(cmd, redir);
}
