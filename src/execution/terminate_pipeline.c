/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:15:41 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/30 11:24:39 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	terminate_pipeline(t_shell *sh, int i, int prev_fd)
{
	sh->exit_status = wait_children(sh, sh->child_pid, i);
	close_fd(&prev_fd);
}
