/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/26 15:55:58 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	free_tab_char(char **tab)
{
	int	i;

	i = 0;
	if (tab && *tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	free_redir_array(t_redir_array redirection)
{
	int	i;

	i = 0;
	if (!redirection.array)
		return ;
	while (i != redirection.size)
	{
		if (redirection.array[i].hd_delimiter)
			free(redirection.array[i].hd_delimiter);
		free(redirection.array[i].filename);
		i++;
	}
	free(redirection.array);
	redirection.array = NULL;
}

void	free_cmd(t_command *cmd)
{
	if (!cmd)
		return;
	if (cmd->cmd)
		free_tab_char(cmd->cmd);
	if (cmd->redirection.array)
		free_redir_array(cmd->redirection);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	cmd = NULL;
}

void	free_tab_cmd(int size, t_command *tab)
{
	int	i;

	i = 0;
	while (i != size)
	{
		free_cmd(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return;
	if (shell->tab)
		free_tab_cmd(shell->tab_size, shell->tab);
	if (shell->env)
		free_tab_char(shell->env);
	shell = NULL;
}
