/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/24 16:07:14 by iwaslet          ###   ########.fr       */
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

int	read_the_input(char **envp)
{
	char		*input;
	t_shell		shell;

	g_signal_received = 0;
	shell = init_shell(envp);
	while (1)
	{
		g_signal_received = 0;
		input = readline("gib comand pliz> ");
		if (g_signal_received == SIGINT)
			g_signal_received = 0;
		handle_eof(input, &shell);
		if (input && !ft_strlen(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		shell.tab = parsing(input, &shell);
		if (shell.tab == NULL)
		{
//			ft_printf("there is no exec_cmd_tab. input : %s\n", input);
			continue ;
		}
		exec_prompt(&shell);
		free(input);
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
