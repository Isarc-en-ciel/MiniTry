/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:11:21 by csteylae          #+#    #+#             */
/*   Updated: 2025/01/30 11:18:47 by csteylae         ###   ########.fr       */
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

t_builtin	*find_builtin(t_shell *sh, t_command *cmd)
{
	int			i;
	t_builtin	*builtin;
	char		*cmd_name;

	i = 0;
	builtin = &sh->builtin[i];
	cmd_name = cmd->cmd[0];
	while (i != 7)
	{
		builtin = &sh->builtin[i];
		if (!ft_strncmp(builtin->name, cmd_name, ft_strlen(builtin->name)))
		{
			return (builtin);
		}
		i++;
	}
	return (NULL);
}

void	exec_builtin(t_builtin *builtin, t_command *cmd, t_shell *sh)
{
	int	status;

	status = builtin->func(&sh->env, cmd, sh->exit_status);
	sh->exit_status = status;
}
