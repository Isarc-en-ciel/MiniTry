/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_one_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:00:32 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/21 17:01:49 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_only_one_builtin(t_shell *sh, int i)
{
	t_builtin	*builtin;

	builtin = find_builtin(sh, &sh->tab[i]);
	if (sh->tab_size != 1)
	{
		return (false);
	}
	if (!builtin)
	{
		return (false);
	}
	perform_redirection(sh, &sh->tab[i]);
	if (sh->tab[i].error.code != OK)
	{
		exit_error(sh, NULL);
	}
	sh->exit_status = builtin->func(&sh->env, &sh->tab[i], sh->exit_status);
	return (true);
}
