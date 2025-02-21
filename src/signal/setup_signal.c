/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:28:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 12:10:50 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

struct sigaction	init_sigaction(void (*signal_handler)(int))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != SUCCESS)
		exit(EXIT_FAILURE);
	return (act);
}

void	setup_signal(t_shell *sh, void(*signal_handler)(int))
{
	sh->signal_act.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sh->signal_act, NULL) != SUCCESS)
		exit_error(sh, "sigaction");
}

struct sigaction	setup_signal_in_children(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != SUCCESS)
		exit(EXIT_FAILURE);
	return (act);
}

struct sigaction	setup_signal_in_parent(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != SUCCESS)
		exit(EXIT_FAILURE);
	return (act);
}
