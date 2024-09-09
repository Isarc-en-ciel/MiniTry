/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/06 15:52:23 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static void	redirect_io(t_shell *shell, int *new_fd_in, int *new_fd_out)
{
	ft_printf("WTHHHHHHHHHHHH\n");
	if (*new_fd_in >= 0)
	{
		if (dup2(*new_fd_in, STDIN_FILENO) < 0)
		{
			ft_printf("yeppppppppppp\n");
			exit_error(shell, "dup2");
		}
		close(*new_fd_in);
		ft_printf("fd_in redirected \n");
	}
	if (*new_fd_out >= 0)
	{
		if (dup2(*new_fd_out, STDOUT_FILENO) < 0)
		{
			ft_printf("ptttttttttttttttn\n");
			exit_error(shell, "dup2");
		}
		close(*new_fd_out);
		ft_printf("fd_out redirected\n");
	}
	ft_printf("no prb with dup2\n\n");
}

//static void	close_fd(t_shell *shell, int n_cmd, int pipe_fd[2], int fd_prev)
//{
//	int	first_cmd;
//	int	last_cmd;
//
//	first_cmd = 0;
//	last_cmd = shell->tab_size;
//	if (n_cmd == first_cmd)
//		close(pipe_fd[READ_FROM]);
//	else if (n_cmd == last_cmd)
//		close(pipe_fd[WRITE_TO]);
//	else
//		close(pipe_fd[READ_FROM]);
//	return;
//}

static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int *fd_prev)
{
	int	first_cmd;
	int	last_cmd;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;
	if (i == first_cmd)
	{
		ft_printf("ok1\n");
		close(pipe_fd[READ_FROM]);
		redirect_io(shell, fd_prev, &pipe_fd[WRITE_TO]);
	}
	else if (i == last_cmd)
	{
		ft_printf("ok end\n");
		close(pipe_fd[READ_FROM]);
		close(pipe_fd[WRITE_TO]);
		redirect_io(shell, fd_prev, (int*)STDOUT_FILENO);
	}
	else
	{
		ft_printf("ok mid\n");
		close(pipe_fd[READ_FROM]);
		redirect_io(shell, fd_prev, &pipe_fd[WRITE_TO]);
	}
	ft_printf("okkkkkkkkkkkkk\n");
}

static void wait_children(pid_t *child_pid, int child_nb)
{
	int	i;

	i = 0;
	while (i != child_nb)
	{
		wait(NULL);
		i++;
	}
	free(child_pid);
	child_pid = NULL;
}

void	exec_pipeline(t_shell *shell)
{
	int	i;
	int	pipe_fd[2];
	pid_t *child_pid;
	int	prev_fd;

	i = 0;
	child_pid = malloc(sizeof(*child_pid) * shell->tab_size);
	if (!child_pid)
		exit_error(shell, "malloc");
	prev_fd = 0;
	while (i != shell->tab_size) //while command arent executed
	{
		//perform_redirections_files()
		ft_printf("nb of iteration %i\n", i);
		if (pipe(pipe_fd) < 0)
			exit_error(shell, "pipe");
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			exit_error(shell, "fork");
		else if (child_pid[i] == 0)
		{
			// prb because i passed value and no pointer so what happens in redirect_pipeline doesnt affect what will be done in exec_cmd ?
			redirect_pipeline(shell, i, pipe_fd, &prev_fd);
			ft_printf("out of redirect_pipeline\n");
			exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
		close(prev_fd);
		prev_fd = pipe_fd[READ_FROM];
		i++;
	}
	close(prev_fd);
	wait_children(child_pid, i);
}
