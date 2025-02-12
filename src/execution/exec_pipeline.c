/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/11 15:26:22 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_child(t_shell *sh, int pipe_fd[2], int prev_fd, int i)
{
	int	exit_status;

	sh->exit_status = sh->tab[i].error.code;
	exit_status = sh->exit_status;
	close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
	free_shell(sh);
	exit(exit_status);
}

static void	launch_cmd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;
	t_builtin	*builtin;

	cmd = &sh->tab[i];
	perform_redirection(sh, &sh->tab[i]);
	if (cmd->error.code != SUCCESS || !cmd->cmd[0])
		exit_child(sh, pipe_fd, prev_fd, i);
	builtin = find_builtin(sh, cmd);
	if (configure_pipeline(sh, i, pipe_fd, prev_fd) == FAIL)
		exit_child(sh, pipe_fd, prev_fd, i);
	if (builtin)
		exec_builtin(builtin, cmd, sh);
	else
	{
		exec_external_command(sh, i);
	}
	exit_child(sh, pipe_fd, prev_fd, i);
}

static int	get_prev_fd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;

	cmd = &sh->tab[i];
	if (close_fd(&pipe_fd[WRITE_TO]) == FAIL || close_fd(&prev_fd) == FAIL)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		cmd->error = set_error(NULL, SYSCALL_ERROR);
		return (NO_REDIR);
	}
	if (cmd->fd_out != NO_REDIR)
		close_fd(&pipe_fd[READ_FROM]);
	return (pipe_fd[READ_FROM]);
}

struct sigaction 	setup_signal_in_children(void)
{
	struct	sigaction act;

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
	struct	sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) != SUCCESS)
		exit(EXIT_FAILURE);
	return (act);
}

void	exec_pipeline(t_shell *sh)
{
	int					pipe_fd[2];
	int					prev_fd;
	int					i;
	struct sigaction	old_act;

	sigaction(SIGINT, NULL, &old_act);
	prev_fd = NO_REDIR;
	i = 0;
	init_child_pid(sh);
	sh->signal_act = setup_signal_in_parent();
	while (i != sh->tab_size)
	{
		init_pipeline(sh, i, pipe_fd, prev_fd);
		if (sh->child_pid[i] == CHILD_PROCESS)
		{
			sh->signal_act = setup_signal_in_children();
			launch_cmd(sh, i, pipe_fd, prev_fd);
		}
		prev_fd = get_prev_fd(sh, i, pipe_fd, prev_fd);
		i++;
	}
	terminate_pipeline(sh, i, prev_fd);
	sigaction(SIGINT, &old_act, NULL);
}
