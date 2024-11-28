/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:56:06 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/28 15:57:33 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	read_the_input(char **envp)
{
	char		*input;
	t_shell		shell;
	t_darray	*tokens;
	t_stock		*tab;

	tab = NULL;
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
		shell.tab = parsing(input, &shell);
        if (shell.tab == NULL)
            continue ;
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
	if (read_the_input(envp) == 1)
		write (1, "ho no it's fucked\n", 18);
	return (0);
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
	if (expander(tab, shell) == -1)
		return (NULL);
	return (NULL);
}
