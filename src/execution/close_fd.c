/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 17:12:48 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/07 14:42:50 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	close_fd(int *fd)
{
	if (*fd > 2)
	{
		if (close(*fd) < 0)
		{
			perror("close");
			*fd = NO_REDIR;
			return (FAIL);
		}
	}
	*fd = NO_REDIR;
	return (SUCCESS);
}

void	close_all_fds(int pipe_fd[2], int *prev_fd, int *in, int *out)
{
	close_fd(&pipe_fd[READ_FROM]);
	close_fd(&pipe_fd[WRITE_TO]);
	close_fd(prev_fd);
	close_fd(in);
	close_fd(out);
}
