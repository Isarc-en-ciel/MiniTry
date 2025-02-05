/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:55:49 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/05 14:25:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_signal_received = SIGINT;
	}
	write(1, "\n", 1);
}

void	handle_ctrl_c(t_shell *sh)
{
	int	i;

	i = 0;
	while (i != sh->tab_size)
	{
	}

}
