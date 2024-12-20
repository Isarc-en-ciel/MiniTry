/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:37:24 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/20 18:03:22 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*The output of each command in the pipeline is connected via a pipe to the input of the next command. 
That is, each command reads the previous command’s output. 
This connection is performed before any redirections specified by command1. 
*/
static void	redirect_pipeline(t_shell *shell, int i, int pipe_fd[2], int prev_fd)
{
	int	first_cmd;
	int	last_cmd;
	int	in;
	int	out;

	first_cmd = 0;
	last_cmd = shell->tab_size - 1;
	in = shell->tab[i].fd_in;
	out = shell->tab[i].fd_out;
	if (i == first_cmd)
	{
		close(pipe_fd[READ_FROM]);
		if (shell->tab[i].fd_in != NO_REDIR)
			in = shell->tab[i].fd_in;
		else
			in = STDIN_FILENO;
		out = pipe_fd[WRITE_TO];
		if (shell->tab[i].fd_out != NO_REDIR)
		{
			close(pipe_fd[WRITE_TO]);
			out = shell->tab[i].fd_out;
		} 
	}
	else if (i == last_cmd)
	{
		//no pipe
		if (prev_fd != NO_REDIR)
			in = prev_fd;
		if (shell->tab[i].fd_in != NO_REDIR)
		{
			close(prev_fd);
			in = shell->tab[i].fd_in;
		}
		if (shell->tab[i].fd_out != NO_REDIR)
			out = shell->tab[i].fd_out;
		else
			out = STDOUT_FILENO;
	}
	else
	{
		close(pipe_fd[READ_FROM]);
		if (prev_fd > -1)
		{
			in = prev_fd;
		}
		else
			in = STDIN_FILENO;
		if (shell->tab[i].fd_in != NO_REDIR)
		{
			if (prev_fd > -1)
				close(prev_fd);
			in = shell->tab[i].fd_in;
		}
		out = pipe_fd[WRITE_TO];
		if (shell->tab[i].fd_out != NO_REDIR)
		{
			close(pipe_fd[WRITE_TO]);
			out = shell->tab[i].fd_out;
		}
	}
	redirect_io(shell, in, out);
}

void	error_pipeline(t_shell *shell, pid_t **children, int pipe_fd[2], int prev_fd)
{
	//should free also child_pid 
	if (*children)
	{
		free(*children);
		children = NULL;
	}
	if (prev_fd > 2)
		close(prev_fd);
	if (pipe_fd[READ_FROM] > 2)
		close(pipe_fd[READ_FROM]);
	if (pipe_fd[WRITE_TO] > 2)
		close(pipe_fd[WRITE_TO]);
	exit_error(shell, NULL);
}

/*The output of each command in the pipeline is connected via a pipe to the input of the next command. 
That is, each command reads the previous command’s output. 
This connection is performed before any redirections specified by command1. 
*/

static bool	init_pipe(t_shell *sh, int i, int tab_size, int pipe_fd[2])
{
	int	last_cmd;

	last_cmd = tab_size - 1;
	if (i == last_cmd)
	{
		return (true);
	}
	if (pipe(pipe_fd) < 0)
	{
		sh->tab[i].error = set_error("pipe", SYSCALL_ERROR);
		return (false);
	}
	else
		return (true);
}

static void	end_pipeline(t_shell *sh, pid_t *child_pid, int prev_fd)
{
	sh->exit_status = wait_children(sh, child_pid);
	if (prev_fd > 2)
		close(prev_fd);
}

bool	is_only_one_builtin(t_shell *sh, int i)
{
	t_builtin	*builtin;

	builtin = find_buildint(sh, sh->tab[i]);
	if (sh->tab_size != 1)
		return (false)
	if (builtin)
	{
		sh->exit_status = builtin.func(&sh->env, sh->tab[i], sh->exit_status);
		return (true);
	}
	else
	{
		return (false);
	}
}

void	launch_cmd(t_shell *sh, int i, int pipe_fd[2], int prev_fd)
{
	t_command *cmd;
	t_builtin *builtin;

	cmd = sh->tab[i];
	builtin = find_builtin(sh, cmd);
	redirect_pipeline(sh, i, pipe_fd, prev_fd);
	if (builtin)
	{
		sh->exit_status = builtin->func(&sh->env, cmd, sh->exit_status);
		//i cannot free in that case the array of pid...but it seems cool and logic that
		//these array belong to the shell struct hell yeah
	}
	else
		exec_command(sh, i);
}

bool	init_fork(int pid, t_command *cmd)
{
	pid = fork();
	if (pid < 0)
	{
		cmd->error = set_error("fork", SYSCALL_ERROR);
		return (false);
	}
	return (true);
}

void	lauch_pipeline(t_shell *sh, int **child_pid, int prev_fd);
{
	int	i;
	int	pipe_fd[2];
	int	*pid;

	i = 0;
	pid = *child_pid;
	while (i != sh->tab_size)
	{
		cmd = sh->tab[i];
		if (!init_pipe(sh, i, sh->tab_size, pipe_fd))
			return ;
		perform_redirection(sh, cmd); //or &sh->tab[i]?
		if (sh->tab[i].error.code != OK)
			continue ;
		if (is_only_one_builtin(sh, i))
			return ;
		if (!init_fork(child_pid[i], cmd))
			return ;
		if (pid[i] == CHILD_PROCESS)
		{
			launch_cmd(sh, i, pipe_fd, prev_fd);
		}
		prev_fd = get_next_cmd_input(pipe_fd, prev_fd); //close the appropriate fds in parent and finds the new prev_fd
		i++;
	}
}

bool	init_pipeline(t_shell *sh, int i, int pipe_fd[2])
{
	if (!init_pipe(sh, i, sh->tab_size, pipe_fd))
	{
		return (false);
	}
	perform_redirection(sh, sh->tab[i]);
	if (sh->tab[i].error.code != OK)
	{
		return (false);
	}
	sh->child_pid[i] = fork();
	if (sh->child_pid < 0)
	{
		sh->tab[i].error = set_error("fork", SYSCALL_ERROR);
		return (false)
	}
	return (true);
}

void	exec_pipeline(t_shell *sh)
{
	int		pipe_fd[2];
	int		prev_fd;
	int		i;

	prev_fd = NO_REDIR;
	i = 0;
	while (i != sh->tab_size)
	{
		if (!init_pipeline())
			return ;
		if (sh->child_pid[i] == CHILD_PROCESS)
		{
			lauch_cmd();
		}
		prev_fd = get_next_input(pipe_fd, prev_fd);
		i++;
	}
	end_pipeline(sh, child_pid, prev_fd);
}
	
/*
void	exec_pipeline(t_shell *shell)
{
	int		i;
	int		pipe_fd[2];
	pid_t	*child_pid;
	int		prev_fd;

	i = 0;
	child_pid = malloc(sizeof(*child_pid) * shell->tab_size);
	if (!child_pid)
		exit_error(shell, "malloc");
	prev_fd = NO_REDIR;
	while (i != shell->tab_size) 
	{
		if (i != shell->tab_size - 1)
		{
			if (pipe(pipe_fd) == -1)
			{
				shell->tab[i].error = set_error("pipe", SYSCALL_ERROR);
				return (error_pipeline(shell, &child_pid, pipe_fd, prev_fd)); //what to do when a pipe error occur ? should we continue to launch the pipeline ? ==> think we can manage it as we want			
			}
		}
		perform_redirection(shell, &shell->tab[i]); //we check the possible error in the child process
		child_pid[i] = fork();
		if (child_pid[i] < 0)
			return (error_pipeline(shell, &child_pid, pipe_fd, prev_fd));
		else if (child_pid[i] == 0)
		{
			if (shell->tab[i].error.code != OK)
				error_pipeline(shell, &child_pid,  pipe_fd, prev_fd);
			redirect_pipeline(shell, i, pipe_fd, prev_fd);
			if (is_builtin(shell, &shell->tab[i]))
			{
				free_shell(shell);
				free(child_pid);
				exit(shell->exit_status);
			}
			else
				exec_command(shell, i);
		}
		close(pipe_fd[WRITE_TO]);
//		if (i != 0 && prev_fd > 2)
//		{
//			close(prev_fd);
//			prev_fd = NO_REDIR;
//		}
		if (prev_fd > 2)
			close(prev_fd);
		if (i != 0 && shell->tab[i - 1].fd_out != NO_REDIR)
		{
			close(pipe_fd[READ_FROM]);
			prev_fd = LAST_PIPE_CLOSED;
		}
		else
		{
			prev_fd = pipe_fd[READ_FROM];
		}
		update_underscore_var(shell); //maybe check this in a better view ?
		i++;
	}
	shell->exit_status = wait_children(shell, child_pid, i);
	if (prev_fd > 2)
		close(prev_fd);
}
*/
