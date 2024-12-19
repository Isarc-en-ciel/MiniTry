/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:07:13 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/19 15:22:15 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(t_shell *sh, t_command *cmd)
{
	int			i;
	t_builtin	builtin;
	char		*cmd_name;

	i = 0;
	builtin = sh->builtin_cmds[i];
	cmd_name = cmd->cmd[0];
	while (i != 7)
	{
		builtin = sh->builtin_cmds[i];
		if (!ft_strncmp(builtin.name, cmd_name, ft_strlen(builtin.name)))
		{
//			return (true);
			sh->exit_status = builtin.func(&sh->env, cmd, sh->exit_status);
			return (true);
		}
		i++;
	}
	return (false);
}

void	exec_simple_cmd(t_shell *shell)
{
	pid_t	pid;

	perform_redirection(shell, &shell->tab[0]);
	if (!shell->tab[0].cmd[0]) // !!
		return ;
	if (shell->tab[0].error.code != OK)
		return ;
	if (is_builtin(shell, &shell->tab[0]))
	{
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
	shell->exit_status = get_exit_status(&shell->tab[0], pid);
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
	{
		exec_simple_cmd(shell);
//		update_underscore_var(shell);
	}
	else
		exec_pipeline(shell);
	shell = clean_prompt(shell);
	ft_printf("exit status : %d\n", shell->exit_status);
	return (0);
}
