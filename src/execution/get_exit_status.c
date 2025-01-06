/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:02:38 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/06 14:50:35 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_exit_status(t_command *cmd, pid_t pid)
{
	pid_t	ret;
	int		status;
	int		exit_status;

	ret = waitpid(pid, &status, 0);
	if (ret == -1)
	{
		cmd->error = set_error("waitpid", SYSCALL_ERROR);
		exit_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
		else
			exit_status = 1;
	}
	return (exit_status);
}

int	wait_children(t_shell *shell, pid_t *child_pid, int child_nb)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i != child_nb)
	{
		exit_status = get_exit_status(&shell->tab[i], child_pid[i]);
		i++;
	}
	return (exit_status);
}
