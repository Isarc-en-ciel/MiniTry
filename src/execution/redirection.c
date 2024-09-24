/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/24 13:14:01 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	open_file(t_shell *shell, t_redirect redir)
{
}

void	perform_redirection(t_shell *shell, t_command cmd)
{
	int	i;

	i = 0;
	if (cmd.redirection.array)
		return ;
	while (i != cmd.redirection.size)
	{
		open_file(shell, cmd.redirection.array[i]);
		i++;

	}


}

