/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:22:47 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/17 11:53:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_shell	init_shell(void)
{
	t_shell shell;

	shell.tab = NULL;
	shell.env = NULL;
	shell.tab_size = 0;
	shell.exit_status = 0;
	return (shell);
}
