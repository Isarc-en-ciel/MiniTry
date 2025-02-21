/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 15:24:02 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_command	get_exec_struct(t_stock stock, int *status)
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

t_command	*from_stock_to_cmd(t_stock *stock_array, t_shell *sh)
{
	t_command	*tab_exec_cmd;
	int			i;
	int			actual_status;

	tab_exec_cmd = NULL;
	i = 0;
	actual_status = 0;
	tab_exec_cmd = malloc(sizeof(*tab_exec_cmd) * stock_array->nbr_cmd);
	if (!tab_exec_cmd)
		exit(EXIT_FAILURE);
	sh->tab_size = stock_array->nbr_cmd;
	while (i != stock_array->nbr_cmd)
	{
		tab_exec_cmd[i] = get_exec_struct(stock_array[i], &actual_status);
		if (actual_status == SYNTAX_ERROR)
		{
			free_second_degree_tab(stock_array, stock_array->nbr_cmd);
			sh = clean_prompt(sh);
			sh->exit_status = actual_status;
			return (NULL);
		}
		i++;
	}
	free_second_degree_tab(stock_array, stock_array->nbr_cmd);
	return (tab_exec_cmd);
}
