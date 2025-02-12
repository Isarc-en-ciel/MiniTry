/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/12 18:06:58 by csteylae         ###   ########.fr       */
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

int	get_token_size(t_stock stock_line, int cmd_size, e_token type)
{
	int	i;
	int	nb_of_type;

	i = 0;
	type_len = 0;
	while (i != cmd_size)
	{
		if (stock_line[i].cmd.type == type)
			nb_of_type++;
		i++;
	}
	return (nb_of_type);
}

t_command transform_stock_to_cmd(t_lexer , int *status)
{
	t_command	exec_cmd;

	exec_cmd.cmd = get_cmd_args(stock_cmd);
	exec_cmd.redirection.array = NULL;
	exec_cmd.redirection.size = 0;
	exec_cmd.fd_in = NO_REDIR;
	exec_cmd.fd_out = NO_REDIR;
	exec_cmd.error.code = SUCCESS;
	exec_cmd.error.str_perror = NULL;
	return (exec_cmd)
}

t_command *from_stock_to_cmd(t_stock *tab, t_shell *sh)
{
	t_command	*tab_exec_cmd;
	int			i;

	tab_exec_cmd = NULL;
	i = 0;
	tab_exec_cmd = malloc(sizeof(*tab_exec_cmd) * nbr_cmd);
	if (!tab_exec_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i != tab.nbr_cmd)
	{
		tab_exec_cmd[i] = transform_lexer_to_cmd(tab.cmd[i], &sh->exit_status);
		if (sh->exit_status != SUCCESS)
		{
			//free everything();
			return (NULL):
		}
		i++;
	}
	return (cmd_tab);
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
	tab = from_stock_to_cmd(tab, shell);
//	free_final_array(tokens);
//	if (expander(tab, shell) == -1)
//		return (NULL);
	return (NULL);
}
