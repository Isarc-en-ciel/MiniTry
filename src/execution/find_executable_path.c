/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:20:45 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/07 11:19:53 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_stat_error(t_command *cmd)
{
	if (errno == ENOENT)
		cmd->error.code = CMD_NOT_FOUND;
	else
		cmd->error = set_error("stat", SYSCALL_ERROR);
}

static void	handle_non_regular_file(t_command *cmd, struct stat stats)
{
	if (S_ISDIR(stats.st_mode))
		cmd->error.code = IS_DIRECTORY;
	else
		cmd->error.code = PERMISSION_DENIED;
}

bool	is_an_executable_file(char *full_path, t_command *cmd)
{
	struct stat	stats;

	if (!full_path)
		return (false);
	if (stat((const char *)full_path, &stats) != 0)
	{
		handle_stat_error(cmd);
		return (false);
	}
	if (!S_ISREG(stats.st_mode))
	{
		handle_non_regular_file(cmd, stats);
		return (false);
	}
	if (stats.st_mode & S_IXUSR)
		return (true);
	else
	{
		cmd->error = set_error(NULL, PERMISSION_DENIED);
		return (false);
	}
}
