/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:33:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/26 15:33:53 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int read_the_input(char **envp)
{
    char *input;
    t_shell  shell;

	shell = init_shell();
	shell.env = init_env(envp);
    while (1)
    {
        input = readline("gib comand pliz> ");
		if (!input)
		{
			ft_printf("Error input is NULL bouuuuh\n");
			break;
		}
		else if (ft_strlen(input) == 0)
			continue;
	//	shell.tab = retrieve_cmd(input); doesnt compile for the moment 
	//	if shell == null -> continue
		add_history(input);
		shell.tab = pseudo_parsing(&shell, input);// simple parsing to test execution
		exec_prompt(&shell);
       	free(input);
	}
    return (0);
}

int main(int ac, char **av, char **envp)
{
    (void)av;

    if (ac != 1)
        return (1);
    read_the_input(envp);
    return (0);
}
