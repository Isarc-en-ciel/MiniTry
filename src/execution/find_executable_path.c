/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:20:45 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/03 14:06:15 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**split_path_var(t_shell *shell, int n)
{
	int		i;
	char	*env_path;
	char	**paths;

	i = 0;
	env_path = NULL;
	paths = NULL;
	if (!shell->env || !shell->env[i])
		return (NULL);
	while (shell->env[i] && ft_strncmp("PATH=", shell->env[i], 5))
		i++;
	if (!shell->env[i])
		return (NULL);
	env_path = shell->env[i] + ft_strlen("PATH=");
	paths = ft_split(env_path, ':');
	if (!paths)
	{
		shell->tab[n].error = set_error("malloc", MALLOC);
		return (NULL);
	}
	return (paths);
}

static char	*construct_path(char *path, char *cmd_name)
{
	char	*slash_cmd;
	char	*full_path;

	slash_cmd = NULL;
	full_path = NULL;
	slash_cmd = ft_strjoin("/", cmd_name, NO_MALLOC);
	if (!slash_cmd)
		return (NULL);
	full_path = ft_strjoin(path, slash_cmd, S2_MALLOC);
	if (!path)
		return (NULL);
	return (full_path);
}

static char	*check_path_accessibility(char *full_path, t_command *cmd)
{
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
			return (full_path);
		else
			cmd->error.code = PERMISSION_DENIED;
	}
	if (access(full_path, F_OK) != 0)
		cmd->error.code = CMD_NOT_FOUND;
	free(full_path);
	full_path = NULL;
	return (NULL);
}

char	*find_executable_path(t_shell *sh, int n, t_command *cmd)
{
	char	**path_array;
	char	*path;
	int		i;

	path_array = NULL;
	path = NULL;
	i = 0;
	path_array = split_path_var(sh, n);
	if (!path_array)
	{
		cmd->error.code = CMD_NOT_FOUND;
		return (NULL);
	}
	while (path_array[i])
	{
		path = construct_path(path_array[i], cmd->cmd[0]);
		if (!path)
			break ;
		path = check_path_accessibility(path, cmd);
		if (path)
			break ;
		i++;
	}
	free_tab_char(path_array);
	return (path);
}
