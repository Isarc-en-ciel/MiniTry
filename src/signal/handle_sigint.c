/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:55:49 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/04 14:14:30 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_eof(char *input, t_shell *shell)
{
	if (!input)
	{
		free_shell(shell);
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

void	handle_sigint_hd(int signum)
{
	g_signal_received = signum;
	close(STDIN_FILENO);
}

