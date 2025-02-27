/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/27 12:50:04 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_eof(char *input, t_shell *shell)
{
	if (!input)
	{
		free_shell(shell);
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

static bool	is_empty(char *input)
{
	if (input && !ft_strlen(input))
	{
		free(input);
		input = NULL;
		return (true);
	}
	return (false);
}

static void	handle_signal(char *input, t_shell *shell)
{
	if (g_signal_received == SIGINT)
		g_signal_received = 0;
	handle_eof(input, shell);
}

/*
void	launch_minishell(char **envp)
{
	char		*input;
	t_shell		shell;

	shell = init_shell(envp);
	set_signal_in_interactive_mode();
	while (1)
	{
		g_signal_received = 0;
		input = readline("gib comand pliz> ");
		handle_signal(input, &shell);
		if (is_empty(input))
			continue;
		add_history(input);
		shell.tab = parsing(input, &shell);
		free(input);
		if (shell.tab == NULL)
			continue ;
		else
			exec_prompt(&shell);
	}
}
*/

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_shell		shell;

	(void)av;
	if (ac != 1)
		return (1);
	shell = init_shell(envp);
	set_signal_in_interactive_mode(&shell);
	while (1)
	{
		g_signal_received = 0;
		input = readline("minishell prompt here> ");
		handle_signal(input, &shell);
		if (is_empty(input))
			continue ;
		add_history(input);
		shell.tab = parsing(input, &shell);
		free(input);
		if (shell.tab == NULL)
			continue ;
		exec_prompt(&shell);
	}
	return (0);
}

t_command	*parsing(char *input, t_shell *shell)
{
	t_darray	*tokens;
	t_stock		*tab;
	t_command	*exec_cmd_tab;

	tab = NULL;
	tokens = retrieve_cmd(input, shell);
	if (tokens == NULL || tokens->content == NULL)
		return (NULL);
	tab = parsing_starter(tokens, tab, shell);
	if (tab == NULL)
		return (NULL);
	free_final_array(tokens);
	tab = expander(tab, shell);
	if (tab == NULL)
		return (error_parsing(tab, 0, shell));
	if (check_grammar(tab, tab[0].nbr_cmd) == 1)
		return (error_parsing(tab, 1, shell));
	exec_cmd_tab = from_stock_to_cmd(tab, shell);
	return (exec_cmd_tab);
}
