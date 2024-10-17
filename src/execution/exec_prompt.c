/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/17 16:31:05 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

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

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	perform_redirection(shell, &shell->tab[0]);
	if (shell->tab[0].error.code != OK)
		return ;
	if (exec_builtin(shell))
	{
		//exec_builtins
		return ;
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	else if (pid == 0)
	{
		redirect_io(shell, shell->tab[0].fd_in, shell->tab[0].fd_out);
		exec_command(shell, 0);
	}
	wait(&shell->exit_status);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	else if (WIFSIGNALED(shell->exit_status))
		shell->exit_status = WTERMSIG(shell->exit_status);
//	delete_heredoc_file(shell->tab);
}

static	t_shell	*clean_prompt(t_shell *shell)
{
	free_tab_cmd(shell->tab_size, shell->tab);
	shell->tab_size = 0;
	shell->tab = NULL;
	return (shell);
}

int	exec_prompt(t_shell *shell)
{
	if (shell->tab_size == 1)
		exec_simple_cmd(shell);
	else
		exec_pipeline(shell);
	shell = clean_prompt(shell);
	ft_printf("exit status : %d\n", shell->exit_status);
	return (0);
}
