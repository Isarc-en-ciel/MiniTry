/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:34:48 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/07 11:29:16 by csteylae         ###   ########.fr       */
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
	if (is_an_executable_file(path, &shell->tab[n]))
	{
		execve(path, shell->tab[n].cmd, shell->env);
		shell->tab[n].error = set_error("execve", SYSCALL_ERROR);
		return ;
	}
	return ;
}

void	print_stat_file_error(t_command *cmd)
{
	if (cmd->error.code == SYSCALL_ERROR)
		return ;
	ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
	if (cmd->error.code == CMD_NOT_FOUND)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	else if (cmd->error.code == PERMISSION_DENIED)
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	else if (cmd->error.code == IS_DIRECTORY)
	{
		cmd->error.code = PERMISSION_DENIED;
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	}
}

void	exec_external_cmd(t_shell *sh, int n)
{
	char			*path;
	t_command		*cmd;

	path = NULL;
	cmd = &sh->tab[n];
	if (ft_strchr(cmd->cmd[0], '/'))
		exec_absolute_path(sh, n);
	else
	{
		path = get_binary_path(sh, n, cmd);
		if (path)
		{
			execve(path, sh->tab[n].cmd, sh->env);
			free(path);
			sh->tab[n].error = set_error("execve", SYSCALL_ERROR);
		}
	}
	print_stat_file_error(cmd);
	return ;
}
