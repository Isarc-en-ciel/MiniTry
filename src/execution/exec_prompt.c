/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/01 16:28:14 by csteylae         ###   ########.fr       */
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

void	open_file(t_shell *shell, int index)
{
	int	i;
	char *in;

	i = 0;
	in = shell->tab[index].in[i].filename;
}
		
void	perform_redirections(t_shell *shell, int index)
{
	t_redirect	*heredoc;
	
	heredoc = shell->tab[index].heredoc;
	if (heredoc)
		exec_heredoc(shell, heredoc);
	open_file(shell, index);
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

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	if (exec_builtin(shell))
	{
		//exec_builtins
		return;
	}
	pid = fork();
	if (pid < 0)
		exit_error(shell, "fork");
	if (pid == 0)
	{
		perform_redirection(shell, &shell->tab[0]);
		exec_command(shell, 0);
	}
	wait(&shell->exit_status);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
	else if (WIFSIGNALED(shell->exit_status))
		shell->exit_status = WTERMSIG(shell->exit_status);
	ft_printf("exit status : %d\n", shell->exit_status);
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
	return (0);
}
