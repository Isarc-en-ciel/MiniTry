/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/24 16:12:10 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	open_file(t_shell *shell, t_redirect redir)
{
	if (redir.type == REDIR_IN)
	{
		close(shell->fd_in);
		shell->fd_in = open(redir.filename, O_RDONLY);
	}
	else if (redir.type == REDIR_OUT)
	{	
		close(shell->fd_out);
		shell->fd_out = open(redir.filename, O_WRONLY | O_TRUNC, O_CREAT, 0644); 
	}
	else if (redir.type == REDIR_APP)
	{
		close(shell->fd_out);
		shell->fd_out = open(redir.filename, O_WRONLY | O_APPEND, O_CREAT, 0644);
	}
}

void	perform_redirection(t_shell *shell, t_command cmd)
{
	int	i;

	i = 0;
	if (cmd.redirection.array)
		return ;
	while (i != cmd.redirection.size)
	{
		open_file(shell, cmd.redirection.array[i]);
		i++;
	}


}

