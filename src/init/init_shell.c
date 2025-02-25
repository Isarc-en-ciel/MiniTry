/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:22:47 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/25 15:36:05 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell	init_shell(char **envp)
{
	t_shell	shell;

	shell.env = init_env(envp);
	shell.tab = NULL;
	shell.tab_size = 0;
	shell.exit_status = 0;
	shell.child_pid = NULL;
	shell.builtin[0].name = "echo";
	shell.builtin[0].func = ft_echo;
	shell.builtin[1].name = "cd";
	shell.builtin[1].func = ft_cd;
	shell.builtin[2].name = "pwd";
	shell.builtin[2].func = ft_pwd;
	shell.builtin[3].name = "export";
	shell.builtin[3].func = ft_export;
	shell.builtin[4].name = "unset";
	shell.builtin[4].func = ft_unset;
	shell.builtin[5].name = "env";
	shell.builtin[5].func = ft_env;
	shell.builtin[6].name = "exit";
	shell.builtin[6].func = ft_exit;
//	shell.signal_act = init_sigaction(&handle_sigint_interactive_mode);
	set_signal_in_interactive_mode(&shell);
	incr_shlvl(&shell);
	return (shell);
}
