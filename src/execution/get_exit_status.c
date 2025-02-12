/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:02:38 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/11 14:42:01 by csteylae         ###   ########.fr       */
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
	{
		exit_status = WEXITSTATUS(status);
//		ft_printf("normal exit with status : %d\n", exit_status);
	}
	else if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
		ft_printf("terminated by signal omg : %d\n", WTERMSIG(status));
	}
	else
		exit_status = 1;
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
//		if (g_signal_received == SIGINT)
//			g_signal_received = 0;
		i++;
	}
	return (exit_status);
}

void	terminate_pipeline(t_shell *sh, int i, int prev_fd)
{
	sh->exit_status = wait_children(sh, sh->child_pid, i);
	close_fd(&prev_fd);
}
