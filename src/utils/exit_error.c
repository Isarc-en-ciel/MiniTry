/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/14 18:38:54 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

void	exit_error(t_shell *shell, char *error_msg)
{
	if (error_msg)
		perror(error_msg);

	free_shell(shell);
	exit(EXIT_FAILURE);
}
