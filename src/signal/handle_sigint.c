/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:55:49 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/07 18:04:44 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int signum)
{
	//it works but rl function arent safe in a signal handler.
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_ctrl_c(t_shell *sh)
{
	int	i;

	i = 0;
	if (!sh->child_pid)
		return ;
	while (i != sh->tab_size)
	{
		kill(sh->child_pid[i], SIGINT);
		i++;
	}
}
