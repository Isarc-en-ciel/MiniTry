/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/06 16:19:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exit_child(t_shell *sh, int pipe_fd[2], int prev_fd, int i)
{
	int	exit_status;

	ft_printf("yes\n");
	exit_status = sh->exit_status;
	close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
	free_shell(sh);
	exit(exit_status);
}

static void	exec_builtin(t_builtin *builtin, t_command *cmd, t_shell *sh)
{
	int	status;

	status = builtin->func(&sh->env, cmd, sh->exit_status);
	sh->exit_status = status;
}

static void	launch_cmd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;
	t_builtin	*builtin;

	cmd = &sh->tab[i];
	builtin = find_builtin(sh, cmd);
	if (sh->tab[i].error.code != OK)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		exit_error(sh, NULL);
	}
	configure_pipeline(sh, i, pipe_fd, prev_fd);
	if (builtin)
	{
		exec_builtin(builtin, cmd, sh);
	}
	else
	{
		exec_command(sh, i);
	}
	exit_child(sh, pipe_fd, prev_fd, i);
}

static int	get_prev_fd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command	*cmd;

	cmd = &sh->tab[i];
	if (close_fd(&pipe_fd[WRITE_TO]) == FAIL)
	{
		close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
		exit_error(sh, NULL);
	}
	close_fd(&prev_fd);
	if (cmd->fd_in != NO_REDIR)
	{
		close_fd(&prev_fd);
	}
	if (cmd->fd_out != NO_REDIR)
	{
		close(pipe_fd[READ_FROM]);
		return (NO_REDIR);
	}
	return (pipe_fd[READ_FROM]);
}

void	exec_pipeline(t_shell *sh)
{
	int		pipe_fd[2];
	int		prev_fd;
	int		i;

	prev_fd = NO_REDIR;
	i = 0;
	if (is_only_one_builtin(sh, i))
		return ;
	if (!init_child_pid(sh))
		return ;
	while (i != sh->tab_size)
	{
		if (!init_pipeline(sh, i, pipe_fd))
		{
			close_all_fds(pipe_fd, &prev_fd, &sh->tab[i].fd_in, &sh->tab[i].fd_out);
			return ;
		}
		if (sh->child_pid[i] == CHILD_PROCESS)
		{
			launch_cmd(sh, i, pipe_fd, prev_fd);
		}
		prev_fd = get_prev_fd(sh, i, pipe_fd, prev_fd);
		i++;
	}
	sh->exit_status = wait_children(sh, sh->child_pid, sh->tab_size);
}
