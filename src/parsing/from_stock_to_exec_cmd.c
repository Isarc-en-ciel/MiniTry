/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/19 20:01:51 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_cmd_args(t_lexer *cmd, int i)
{
	if (i == 0 && !is_redir_operator(cmd[i].type))
		return (true);
	else if (i > 0 && !is_redir_operator(cmd[i - 1].type)
		&& !is_redir_operator(cmd[i].type))
	{
		return (true);
	}
	else
		return (false);
}

static int	get_cmd_args_size(t_lexer *cmd, int cmd_size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i != cmd_size)
	{
		if (is_cmd_args(cmd, i))
			len++;
		i++;
	}
	return (len);
}

static char	**get_cmd_args(t_lexer *cmd, int cmd_size)
{
	int		i;
	int		len;
	char	**cmd_args;

	i = 0;
	len = 0;
	cmd_args = malloc(sizeof(char *) * (get_cmd_args_size(cmd, cmd_size) + 1));
	if (!cmd_args)
		exit_error(NULL, "malloc");
	while (i != cmd_size)
	{
		if (is_cmd_args(cmd, i))
		{
			cmd_args[len] = ft_strdup(cmd[i].word);
			if (!cmd_args[len])
				exit_error(NULL, NULL);
			len++;
		}
		i++;
	}
	cmd_args[len] = NULL;
	return (cmd_args);
}

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
			return (NULL);
		}
		i++;
	}
	free_second_degree_tab(stock_array, stock_array->nbr_cmd);
	return (tab_exec_cmd);
}
