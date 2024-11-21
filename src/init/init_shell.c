/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:22:47 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/20 11:54:43 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_export(char ***env, t_command *cmd)
{
	(void)cmd;
	(void)env;
	ft_printf("this is export !\n");
	return (0);
}

int	ft_unset(char ***env,t_command *cmd)
{
	(void)cmd;
	(void)env;
	ft_printf("this is unset!\n");
	return (0);
}

int	ft_exit(char ***env, t_command *cmd)
{
	(void)cmd;
	(void)env;
	ft_printf("this is exit !\n");
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
