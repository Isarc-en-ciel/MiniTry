/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:09 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/03 19:49:57 by csteylae         ###   ########.fr       */
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


void	handle_sigint_hd(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
	//	write(1, "\n", 1);
		exit(130);
	}
}

static void	setup_heredoc_signals(t_shell *sh, int fd)
{
	struct sigaction	hd_sigquit;
	struct sigaction	hd_sigint;

	ft_bzero(&hd_sigquit, sizeof(hd_sigquit));
	hd_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&hd_sigquit.sa_mask);
	hd_sigquit.sa_flags = 0;
	if (sigaction(SIGQUIT, &hd_sigquit, NULL) != SUCCESS)
	{
		close_fd(&fd);
		exit_error(sh, "sigaction");
	}
	
	ft_bzero(&hd_sigint, sizeof(hd_sigint));
	hd_sigint.sa_handler = handle_sigint_hd;
	sigemptyset(&hd_sigint.sa_mask);
	if (sigaction(SIGINT, &hd_sigint, NULL) != SUCCESS)
	{
		close_fd(&fd);
		exit_error(sh, "sigaction");
	}
}

static void	write_heredoc(t_shell *sh, int fd, t_redirect *rdir)
{
	char	*line;

	line = NULL;
	setup_heredoc_signals(sh, fd);
	while (1)
	{
		line = readline("> "); 
		if (!line)
		{
			ft_printf("warning : heredoc terminate with eof\n");
			break ;
		}
		if (key_found(rdir->hd_delimiter, line))
			break ;
		handle_hd_expansion(&line, fd, sh, rdir);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	free_shell(sh);
	exit(EXIT_SUCCESS);
}

static void	get_hd_filename(t_command *cmd, t_redirect *redir)
{
	free(redir->filename);
	redir->filename = ft_strdup(HEREDOC_FILE);
	if (!redir->filename)
		cmd->error = set_error("malloc", MALLOC);
}

static int	open_hd(t_command *cmd)
{
	int	heredoc; 

	heredoc = open(HEREDOC_FILE, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (heredoc < 0)
	{
		cmd->error = set_error("heredoc", SYSCALL_ERROR);
	}
	return (heredoc);
}

void	create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redir)
{
	int					heredoc;
	int					pid;
//	struct sigaction	old_sigint;
	struct sigaction	old_sigquit;

   	sigaction(SIGQUIT, NULL, &old_sigquit);
 //  	sigaction(SIGINT, NULL, &old_sigint);
	heredoc = open_hd(cmd);
	if (heredoc == -1)
		return ;
	pid = fork();
	if (pid < 0)
	{
		cmd->error = set_error("fork", SYSCALL_ERROR);
		return ;
	}
	if (pid == CHILD_PROCESS)
		write_heredoc(shell, heredoc, redir);
	shell->exit_status = get_exit_status(cmd, pid); 
	sigaction(SIGQUIT, &old_sigquit, NULL);
//	sigaction(SIGINT, &old_sigint, NULL);
	cmd->error.code =  shell->exit_status;
	close(heredoc);
	get_hd_filename(cmd, redir);
}
