/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/09 18:50:06 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"
/*
void	exec_heredoc(t_shell *shell, t_redirect *heredoc)
{
	(void) shell;
	(void)heredoc;
	return;
}
*/
bool	exec_builtin(t_shell *shell)
{
	char **cmd;

	cmd = shell->tab->cmd;
	if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		exec_env(shell);
	else
		return (false);
	return (true);
}

void	delete_heredoc_file(t_command *cmd)
{
	int	i;

	i = 0;
	if (cmd->redirection.size == 0)
		return ;
	while (i != cmd->redirection.size)
	{
		if (cmd->redirection.array[i].type == REDIR_HEREDOC)
		{
			if (access(cmd->redirection.array[i].filename, F_OK) == 0)
				unlink(cmd->redirection.array[i].filename);
		}
		i++;
	}
}

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	perform_redirection(shell, &shell->tab[0]);
	ft_printf("fd_in : %d, fd_out : %d\n", shell->tab[0].fd_in,shell->tab[0].fd_out); 
	if (shell->tab[0].error.code == OPEN_FILE)
		exit_error(shell, shell->tab[0].error.str_perror);
	if (exec_builtin(shell))
	{
		//exec_builtins
		return;
	}
	pid = fork();
	if (pid < 0)
		exit_error(shell, "fork");
	else if (pid == 0)
	{
//		perform_redirection(shell, &shell->tab[0]);
//		if (shell->tab[0].error.code == OPEN_FILE)
//			exit_error(shell, shell->tab[0].error.str_perror);
		redirect_io(shell, shell->tab[0].fd_in, shell->tab[0].fd_out);
		exec_command(shell, 0);
	}
	ft_printf("ok\n");
	wait(&shell->exit_status);
//	if (WIFEXITED(shell->exit_status))
//		shell->exit_status = WEXITSTATUS(shell->exit_status);
//	else if (WIFSIGNALED(shell->exit_status))
//		shell->exit_status = WTERMSIG(shell->exit_status);
//	delete_heredoc_file(shell->tab);
}

int	exec_prompt(t_shell *shell)
{
	int	nb;

	nb = shell->tab_size;
	if (nb == 1)
		exec_simple_cmd(shell);
	else
		exec_pipeline(shell);
	free_tab_cmd(shell->tab_size, shell->tab);
	shell->tab_size = 0;
	shell->tab = NULL;
	ft_printf("exit status : %d\n", shell->exit_status);
	return (0);
}
