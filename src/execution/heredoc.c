/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:52:09 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/14 16:52:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redir)
{
	char	*line;
	int		heredoc;
	int		pid;

	line = NULL;
	if (access("/Users/csteylae/goinfre/minishell_heredoc", F_OK) == 0)
		unlink("/Users/csteylae/goinfre/minishell_heredoc");
	heredoc = open("/Users/csteylae/goinfre/minishell_heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (heredoc == -1)
		cmd->error = set_error("heredoc", OPEN_FILE);
	pid = fork();
	if (pid < 0)
		return ;
		//manage error and return it to the level of the exec_pipeline
	else if (pid == 0)
	{
		while (1)
		{
			write(STDOUT_FILENO, "> ", 2);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(redir->hd_delimiter, line, ft_strlen(redir->hd_delimiter)) == 0
   	            && line[ft_strlen(redir->hd_delimiter)] == '\n')
					break;
			write(heredoc, line, ft_strlen(line));
			free(line);
			line = NULL;
		}
	free(line);
	close(heredoc);
	free_shell(shell);
	exit(EXIT_SUCCESS);
	}
	waitpid(pid, NULL, 0);
	close(heredoc);
	free(redir->filename);
	redir->filename = ft_strdup("/Users/csteylae/goinfre/minishell_heredoc");
	if (!redir->filename)
		//manage_error;
	return ;
}
