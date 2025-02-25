/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:28:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/25 13:30:52 by csteylae         ###   ########.fr       */
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

/*
void	setup_signal(t_shell *sh, void (*signal_handler) (int))
{
	sh->signal_act.sa_handler = signal_handler;
	if (sigaction(SIGINT, &sh->signal_act, NULL) != SUCCESS)
		exit_error(sh, "sigaction");
}
*/

struct sigaction	setup_signal_in_children(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	return (act);
}

void	set_signal_in_children(t_shell *sh)
{
	struct sigaction	sigint_in_child;
	struct sigaction	sigquit_in_child;

	sigint_in_child = setup_signal_in_children();
	sigquit_in_child = setup_signal_in_children();
	if (sigaction(SIGINT, &sigint_in_child, NULL) != SUCCESS)
		exit_error(sh, "sigaction");
	if (sigaction(SIGQUIT, &sigquit_in_child, NULL) != SUCCESS)
		exit_error(sh, "sigaction");
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
