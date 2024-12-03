/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:22:47 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/03 15:18:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	(void)cmd, 
	(void) exit_status;
	(void)env;
	ft_printf("this is export !\n");
	return (0);
}

t_shell	init_shell(void)
{
	t_shell shell =	
	{
		.tab = NULL,
		.env = NULL,
		.tab_size = 0,
		.exit_status = 0,
		.builtin_cmds = 
		{ 
			{ "echo", &ft_echo },
			{ "cd", ft_cd },
			{ "pwd", ft_pwd },
			{ "export", ft_export },
			{ "unset", ft_unset },
			{ "env", ft_env },
			{ "exit", ft_exit }
		},
	};
	return (shell);
}
