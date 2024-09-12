/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/05 15:08:57 by csteylae         ###   ########.fr       */
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
//	else if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
	else
		return (false);
	return (true);
}

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

//	cmd = shell->tab->cmd;
//	perform_redirections(shell, 0);
	if (exec_builtin(shell))
		return;
	pid = fork();
	if (pid < 0)
		exit_error(shell, "fork");
	if (pid == 0)
		exec_command(shell, 0);
	shell->exit_status = wait(NULL);
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
	ft_printf("end of execution\n");
	return (0);
}
