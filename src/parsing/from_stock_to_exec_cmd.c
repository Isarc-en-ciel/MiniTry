/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/25 14:29:37 by iwaslet          ###   ########.fr       */
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

void	syntax_error(t_stock *stock_array, t_shell *sh, t_command *tab_exec_cmd)
{
	free_second_degree_tab(stock_array, stock_array->nbr_cmd);
	free(tab_exec_cmd);
	sh = clean_prompt(sh);
	sh->exit_status = SYNTAX_ERROR;
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
			syntax_error(stock_array, sh, tab_exec_cmd);
			return (NULL);
		}
		i++;
	}
	free_second_degree_tab(stock_array, stock_array->nbr_cmd);
	return (tab_exec_cmd);
}
