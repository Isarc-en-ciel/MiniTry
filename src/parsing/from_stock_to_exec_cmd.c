/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_exec_cmd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:45:31 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/14 12:50:25 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_token_len(int size, t_lexer *tab, enum e_tokens type)
{
	int	i;
	int	token_nb;

	i = 0;
	token_nb = 0;
	if (!tab)
	{
		ft_printf("can not count ft_token_size :(\n");
		return (0);
	}
	while (i != size)
	{
		if (&tab[i] && tab[i].type == type)
			token_nb++;
		i++;
	}
	return (token_nb);
}

bool	is_redir_operator(enum e_tokens type)
{
	if (type == REDIR_IN 
		|| type == REDIR_OUT
		|| type == REDIR_HEREDOC
		|| type == REDIR_APP)
	{
		return (true);
	}
	return (false);
}

bool	is_valid_redir_syntax(t_lexer *cmd, int i, int cmd_size)
{
	if (is_redir_operator(cmd[i].type && i == cmd_size))
		return (false);
	if (is_redir_operator(cmd[i].type && &cmd[i + 1] && !is_redir_operator(cmd[i + 1].type)))
		return (true);
	else
		return (false);
}

int	check_redirection_operator(t_lexer *cmd, int cmd_size)
{
	int	nb_of_redir;
	int	i;

	nb_of_redir = 0;
	i = 0;
	while (i != cmd_size)
	{
		if (is_redir_operator(cmd[i].type))
		{
			if (!is_valid_redir_syntax(cmd, i, cmd_size))
				return (-1);
			nb_of_redir++;
		}
		i++;
	}
	return (nb_of_redir);
}

t_redirect	*create_redirection_array(int array_size, t_lexer *cmd, int cmd_size)
{
	int			i;
	int			j;
	t_redirect	*r_array;

	i = 0;
	j = 0;
	r_array = malloc(sizeof(t_redirect) * array_size);
	if (!r_array)
		return (NULL);
	while (i != cmd_size)
	{
		if (is_redir_operator(cmd[i].type))
		{
			r_array[j].type = cmd[i].type;
			i++;
			if (array_size && r_array[j].type == REDIR_HEREDOC)
			{
				r_array[j].hd_delimiter = ft_strdup(cmd[i].word);
				r_array[j].filename = NULL;
			}
			else
			{
				r_array[j].filename = ft_strdup(cmd[i].word);
				r_array[j].hd_delimiter = NULL;
			}
			j++;
		}
		i++;
	}
	if (j != array_size)
		ft_printf("wtf not the good nb of redir\n");
	return (r_array);
}

t_redir_array	get_redirection_array(t_lexer *cmd, int cmd_size, int *pstatus)
{
	t_redir_array	redir_array;

	redir_array.size = check_redirection_operator(cmd, cmd_size);
	if (redir_array.size < 0)
	{
		*pstatus = SYNTAX_ERROR;
		return (redir_array);
	}
	if (redir_array.size == 0)
	{
		redir_array.array = NULL;
		return (redir_array); //there is no redirection
	}
	redir_array.array = create_redirection_array(redir_array.size, cmd, cmd_size);
	return (redir_array);
}

t_command get_exec_struct(t_stock stock, int *status)
{
	t_command	exec_cmd;

	exec_cmd.redirection = get_redirection_array(stock.cmd, stock.nbr_elem, status);
	exec_cmd.cmd = NULL;//get_cmd_args(stock.nbr_elem, stock.cmd);
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
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i != stock_array->nbr_cmd)
	{
		tab_exec_cmd[i] = get_exec_struct(stock_array[i], &sh->exit_status);
		if (sh->exit_status != SUCCESS)
		{
			//free everything();
			return (NULL);
		}
		i++;
	}
	return (tab_exec_cmd);
}
