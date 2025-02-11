/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:55:49 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/11 13:56:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint_interactive_mode(int signum)
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

void	handle_sigint_child_process(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
		write(1, "\n", 1);
	}
}
