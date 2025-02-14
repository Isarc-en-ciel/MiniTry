/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/14 11:31:34 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

void	handle_eof(char *input, t_shell *shell)
{
	if (!input)
	{
		free_shell(shell);
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

int	read_the_input(char **envp)
{
	char		*input;
	t_shell		shell;

	g_signal_received = 0;
	shell = init_shell(envp);
	while (1)
	{
		g_signal_received = 0;
	//	setup_signal(&shell, &handle_sigint_interactive_mode);
		input = readline("gib comand pliz> ");
		if (g_signal_received == SIGINT)
		{
			g_signal_received = 0;
		}
		handle_eof(input, &shell);
		if (input && !ft_strlen(input)) //if the input is just spaces
		{
			free(input);
			continue;
		}
		add_history(input);
//		shell.tab = pseudo_parsing(&shell, input);
		shell.tab = parsing(input, &shell);
		if (shell.tab == NULL)
			continue ;
		exec_prompt(&shell);
		free(input);
		g_signal_received = 0;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (1);
	if (read_the_input(envp) == 1)
		write (1, "ho no it's fucked\n", 18);
	return (0);
}

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

bool	is_redir_operator(enum e_token type)
{
	if (type == REDIR_IN 
		|| type == REDIR_OUT
		|| type == REDIR_HEREDOR
		|| type == REDIR_APPEND)
	{
		return (true);
	}
	return (false);
}

bool	is_valid_redir_syntax(t_lexer *cmd, int i, int cmd_size)
{
	if (is_redir_operator(cmd[i].type && i == cmd_size))
		return (false); // if the redir operator is the last elem of the cmd
	if (is_redir_operator(cmd[i].type && &cmd[i + 1] && !is_redir_operator(&cmd[i + 1])))
		return (true); // if the elem that follows a redir operator isnt a redir operator then its valid
	else
		return (false); // if the operator isnt the last elem and if the following elem is another redir
}

int	check_redirection_operator(t_lexer *cmd, int cmd_size)
{
	int	nb_of_redir;
	int	i;

	nb_of_redir = 0;
	i = 0;
	while (i != cmd_size && )
	{
		if (is_redir_operator(cmd[i].type))
		{
			if (!is_valid_redir_syntax(cmd, i, cmd_cmd_size))
				return (-1);
			nb_of_redir++;
		}
		i++;
	}
	return (nb_of_redir);
}

t_redir_array	get_redirection_array(t_lexer *cmd, int cmd_size, int *pstatus)
{
	t_redir_array	redir_array;
	int				i;
	int				nb_of_redir;

	i = 0;
	redir_array.size = check_redirection_operator(cmd, cmd_size);
	if (redir_array.size < 0)
	{
		pstatus = SYNTAX_ERROR;
		return (redir_array);
	}
	if (redir_array.size == 0)
	{
		redir_array->array = NULL;
		return (redir_array); //there is no redirection
	}
	redir_array



	return (redir_array);
}

t_command get_exec_struct(t_stock stock, int *status)
{
	t_command	exec_cmd;

	//check syntax(). the only point is if type == redir, type +1 = word
	//we are going to modify the structure t_stock to remove the elements identified as filename/hd del
	exec_cmd.redirection = get_redirection_array(&stock.cmd, stock.nbr_elem, status);
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

t_command	*parsing(char *input, t_shell *shell)
{
	t_darray	*tokens;
	t_stock		*tab;

	tab = NULL;
	tokens = retrieve_cmd(input);
	if (tokens == NULL || tokens->content == NULL)
		return (NULL);
	tab = parsing_starter(tokens, tab);
	if (tab == NULL)
		return (NULL);
	free_final_array(tokens);
	shell->tab = from_stock_to_cmd(tab, shell);
//	free_final_array(tokens);
//	if (expander(tab, shell) == -1)
//		return (NULL);
	return (NULL);
}
