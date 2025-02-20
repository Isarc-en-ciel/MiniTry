/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:34:48 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/20 16:00:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* 
 * first construct the path from the var_env PATH, add the "/cmd" to the path 
 * then try to access the executable via access() with the X_OK flag 
 * if an access is found the command will be executed with execve()
 * that will exit the programm
 * if no path was found we need to manage the error appropriately
 */

static void	exec_absolute_path(t_shell *shell, int n)
{
	char	*path;

	path = shell->tab[n].cmd[0];
	if (access(path, X_OK) == 0)
	{
		if (execve(path, shell->tab[n].cmd, shell->env) < 0)
		{
			shell->tab[n].error = set_error("execve", SYSCALL_ERROR);
			return ;
		}
	}
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		shell->tab[n].error = set_error(path, FAIL);
	else
		shell->tab[n].error = set_error(path, CMD_NOT_FOUND);
}

static void	exec_command(char *path, t_shell *sh, int n)
{
	execve(path, sh->tab[n].cmd, sh->env);
	free(path);
	sh->tab[n].error = set_error("execve", SYSCALL_ERROR);
}

void	exec_external_command(t_shell *shell, int n)
{
	char			*path;
	t_command		*cmd;

	path = NULL;
	cmd = &shell->tab[n];
	if (ft_strchr(cmd->cmd[0], '/'))
		return (exec_absolute_path(shell, n));
	path = find_executable_path(shell, n, cmd);
	if (path)
		return (exec_command(path, shell, n));
	else
	{
		ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
		if (cmd->error.code == CMD_NOT_FOUND)
			ft_putstr_fd(" : command not found\n", STDERR_FILENO);
		else if (cmd->error.code == FILE_NO_PERM)
			ft_putstr_fd(" : permission denied\n", STDERR_FILENO);
	}
}
