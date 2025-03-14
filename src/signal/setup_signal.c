/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:28:14 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/04 14:59:23 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_signal_in_interactive_mode(t_shell *shell)
{
	struct sigaction	interupt;
	struct sigaction	quit;

	ft_bzero(&interupt, sizeof(interupt));
	interupt.sa_handler = handle_sigint_interactive_mode;
	sigemptyset(&interupt.sa_mask);
	interupt.sa_flags = 0;
	if (sigaction(SIGINT, &interupt, NULL) != SUCCESS)
		exit_error(shell, "sigaction");
	ft_bzero(&quit, sizeof(quit));
	quit.sa_handler = SIG_IGN;
	sigemptyset(&quit.sa_mask);
	quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &quit, NULL) != SUCCESS)
		exit_error(shell, "sigaction");
}

static struct sigaction	setup_signal_in_children(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_DFL;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	return (act);
}

void	set_signal_in_child(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	struct sigaction	sigint_in_child;
	struct sigaction	sigquit_in_child;

	sigint_in_child = setup_signal_in_children();
	sigquit_in_child = setup_signal_in_children();
	if (sigaction(SIGINT, &sigint_in_child, NULL) != SUCCESS)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		exit_error(sh, "sigaction");
	}
	if (sigaction(SIGQUIT, &sigquit_in_child, NULL) != SUCCESS)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		exit_error(sh, "sigaction");
	}
}

struct sigaction	set_signal_in_parent(t_shell *sh)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != SUCCESS)
		exit_error(sh, "sigaction");
	return (act);
}

void	setup_heredoc_signals(t_shell *sh, int fd)
{
	struct sigaction	hd_sigquit;
	struct sigaction	hd_sigint;

	ft_bzero(&hd_sigquit, sizeof(hd_sigquit));
	hd_sigquit.sa_handler = SIG_IGN;
	sigemptyset(&hd_sigquit.sa_mask);
	hd_sigquit.sa_flags = 0;
	if (sigaction(SIGQUIT, &hd_sigquit, NULL) != SUCCESS)
	{
		close_fd(&fd);
		exit_error(sh, "sigaction");
	}
	ft_bzero(&hd_sigint, sizeof(hd_sigint));
	hd_sigint.sa_handler = handle_sigint_hd;
	sigemptyset(&hd_sigint.sa_mask);
	if (sigaction(SIGINT, &hd_sigint, NULL) != SUCCESS)
	{
		close_fd(&fd);
		exit_error(sh, "sigaction");
	}
}
