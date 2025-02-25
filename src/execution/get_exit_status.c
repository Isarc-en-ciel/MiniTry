/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:02:38 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/25 16:38:43 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_exit_status(t_command *cmd, pid_t pid)
{
	int		status;
	int		exit_status;

	(void) cmd;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
		if (exit_status == 130 || exit_status == 131)
			write(1, "\n", 1);
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

void	terminate_pipeline(t_shell *sh, int i, int prev_fd)
{
	sh->exit_status = wait_children(sh, sh->child_pid, i);
	close_fd(&prev_fd);
}
