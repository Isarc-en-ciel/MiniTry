/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:33:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/15 14:31:19 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

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
			return (1);
		parsing_starter(tokens);
		//shell.tab = pseudo_parsing(&shell, input);// simple parsing to test execution
		//exec_prompt(&shell);
		free(input);
		input = NULL;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (1);
	read_the_input(envp);
	return (0);
}
