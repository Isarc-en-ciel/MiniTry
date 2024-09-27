/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:34:48 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/27 17:20:55 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

/* 
 * first construct the path from the var_env PATH, add the "/cmd" to the path 
 * then try to access the executable via access() with the X_OK flag 
 * if an access is found the command will be executed with execve() that will exit the programm
 * if no path was found we need to manage the error appropriately
 *
 * */
static void	exec_error(char **path, t_shell *shell, char *msg_error)
{
	if (path)
		free_tab_char(path);
	exit_error(shell, msg_error);
}

static void	search_absolute_path(t_shell *shell, int n)
{
	char *path;

	if (!ft_strchr(shell->tab[n].cmd[0], '/'))
		return;
	path = shell->tab[n].cmd[0];
	if (access(path, X_OK) == 0)
	{
		if (execve(path, shell->tab[n].cmd, shell->env) < 0)
			exec_error(NULL, shell, "execve");
	}
	exec_error(NULL, shell, shell->tab[n].cmd[0]);
}

static char **get_path(char **env)
{
	int	i;
	char *env_path;

	i = 0;
	env_path = NULL;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	env_path = env[i] + ft_strlen("PATH=");
	return (ft_split(env_path, ':'));
}

static char	*add_cmd_path(char *path, char *cmd)
{
	char *cmd_path; 

	cmd_path = ft_strjoin("/", cmd, NO_MALLOC);
	if (!cmd_path)
		return (NULL);
	path = ft_strjoin(path, cmd_path, BOTH_MALLOC);
	if (!path)
		return (NULL);
	return (path);
}

void	exec_command(t_shell *shell, int n)
{
	int		i;
	char	**path;

	i = 0;
	search_absolute_path(shell, n);
	path = get_path(shell->env);
	if (!path)
		exec_error(path, shell, "malloc");
	while (path[i])
	{
		path[i] = add_cmd_path(path[i], shell->tab[n].cmd[0]);
		if (!path[i])
			exec_error(path, shell, "malloc");
		if (access(path[i], X_OK) == 0)
		{
			execve(path[i], shell->tab[n].cmd, shell->env);
			exec_error(path, shell, "execve");
		}
		i++;
	}
	exec_error(path, shell, shell->tab[n].cmd[0]);
}
