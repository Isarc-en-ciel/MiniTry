/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:52:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/20 15:06:35 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_error(t_shell *shell, char *error_msg)
{
	if (error_msg)
		perror(error_msg);
	free_shell(shell);
	exit(EXIT_FAILURE);
}
