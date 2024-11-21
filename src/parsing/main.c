/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/21 13:16:05 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	read_the_input(char **envp)
{
	char		*input;
	t_shell		shell;
	t_darray	*tokens;

	shell = init_shell();
	shell.env = init_env(envp);
	tokens = NULL;
	while (1)
	{
		input = readline("gib comand pliz> ");
		if (!input)
		{
			ft_printf("Error input is NULL bouuuuh\n");
			break ;
		}
		else if (ft_strlen(input) == 0)
			continue ;
		add_history(input);
		tokens = retrieve_cmd(input);
		if (tokens == NULL || tokens->content == NULL)
			continue ;
		if (parsing_starter(tokens) == 1)
		{
			free_final_array(tokens);
			continue ;
		}
	//	shell.tab = retrieve_cmd(input); doesnt compile for the moment 
	//	if shell == null -> continue
		shell.tab = pseudo_parsing(&shell, input);// simple parsing to test execution
		exec_prompt(&shell);
		free(input);
		free_final_array(tokens);
		input = NULL;
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
