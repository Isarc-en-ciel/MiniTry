/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:22:47 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/24 15:26:20 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

int	ft_echo(char **args)
{
	(void)args;
	ft_printf("this is echo\n");
	return (0);
}

int	ft_pwd(char **args)
{
	(void)args;
	ft_printf("this is pwd\n");
	return (0);
}

int	ft_export(char **args)
{
	(void)args;
	ft_printf("this is export !\n");
	return (0);
}

int	ft_unset(char **args)
{
	(void)args;
	ft_printf("this is unset!\n");
	return (0);
}

int	ft_env(char **args)
{
	(void)args;
	ft_printf("this is env !\n");
	return (0);
}

int	ft_exit(char **args)
{
	(void)args;
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
