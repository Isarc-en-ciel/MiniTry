/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/19 18:49:16 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_cmd_args(t_lexer *cmd, int cmd_size)
{
	int		i;
	int		len;
	char	**cmd_args;

	i = 0;
	len = 0;
	cmd_args = NULL;
	while (i != cmd_size)
	{
		if (i > 0 && !is_redir_operator(cmd[i - 1].type) && !is_redir_operator(cmd[i].type))
			len++;
		else if (i == 0 && !is_redir_operator(cmd[i].type))
			len++;
		i++;
	}
	cmd_args = malloc(sizeof(char *) * (len + 1));
	if (!cmd_args)
		exit_error(NULL, "malloc");
	i = 0;
	len = 0;
	while (i != cmd_size)
	{
		if (i == 0 && !is_redir_operator(cmd[i].type))
		{
			cmd_args[len] = ft_strdup(cmd[i].word);
			len++;
		}
		else if (i > 0 && !is_redir_operator(cmd[i - 1].type) && !is_redir_operator(cmd[i].type))
		{
			cmd_args[len] = ft_strdup(cmd[i].word);
			len++;
		}
		i++;
	}
	cmd_args[len] = NULL;
	return (cmd_args);
}

t_command get_exec_struct(t_stock stock, int *status)
{
	t_command	exec_cmd;

	exec_cmd.redirection = get_redirections(stock.cmd, stock.nbr_elem, status);
	exec_cmd.cmd = get_cmd_args(stock.cmd, stock.nbr_elem);
	exec_cmd.fd_in = NO_REDIR;
	exec_cmd.fd_out = NO_REDIR;
	exec_cmd.error.code = SUCCESS;
	exec_cmd.error.str_perror = NULL;
	return (exec_cmd);
}

t_command *from_stock_to_cmd(t_stock *stock_array, t_shell *sh)
{
	t_command	*tab_exec_cmd;
	int			i;

	tab_exec_cmd = NULL;
	i = 0;
	tab_exec_cmd = malloc(sizeof(*tab_exec_cmd) * stock_array->nbr_cmd);
	if (!tab_exec_cmd)
		exit(EXIT_FAILURE);
	sh->tab_size = stock_array->nbr_cmd;
	while (i != stock_array->nbr_cmd)
	{
		tab_exec_cmd[i] = get_exec_struct(stock_array[i], &sh->exit_status);
		if (sh->exit_status == SYNTAX_ERROR)
		{
			//free everything();
			return (NULL);
		}
		i++;
	}
	free_second_degree_tab(stock_array, stock_array->nbr_cmd);
	return (tab_exec_cmd);
}
