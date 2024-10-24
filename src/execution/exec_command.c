/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:34:48 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/22 11:01:17 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

/* 
 * first construct the path from the var_env PATH, add the "/cmd" to the path 
 * then try to access the executable via access() with the X_OK flag 
 * if an access is found the command will be executed with execve()
 * that will exit the programm
 * if no path was found we need to manage the error appropriately
 */

static void	exec_error(char **path, t_shell *shell, char *str)
{
	if (path)
		free_tab_char(path);
	exit_error(shell, str);
}

static void	search_absolute_path(t_shell *shell, int n)
{
	char	*path;

	path = shell->tab[n].cmd[0];
	if (!ft_strchr(path, '/'))
		return ;
	if (access(path, X_OK) == 0)
	{
		if (execve(path, shell->tab[n].cmd, shell->env) < 0)
			exec_error(NULL, shell, "execve");
	}
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		shell->tab[n].error = set_error(path, FILE_NO_PERM);
	else
		shell->tab[n].error = set_error(path, CMD_NOT_FOUND);
	exec_error(NULL, shell, NULL);
}

static char	**split_path_var(t_shell *shell, int n)
{
	int		i;
	char	*env_path;
	char	**paths;

	i = 0;
	env_path = NULL;
	paths = NULL;
	if (!shell->env || !*shell->env)
		return (NULL);
	while (shell->env[i] && ft_strncmp("PATH=", shell->env[i], 5)) //not enough
		i++;
	if (!shell->env[i])
		return (NULL);
	env_path = shell->env[i] + ft_strlen("PATH=");
	paths = ft_split(env_path, ':');
	if (!paths)
		shell->tab[n].error = set_error("malloc", MALLOC);
	return (paths);
}

static char	*test_path(char *path, char *cmd_name, enum e_error *code)
{
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", cmd_name, NO_MALLOC);
	if (!slash_cmd)
	{
		*code = MALLOC;
		return (NULL);
	}
	path = ft_strjoin(path, slash_cmd, BOTH_MALLOC);
	if (!path)
	{
		*code = MALLOC;
		return (NULL);
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
			return (path);
		else
			*code = FILE_NO_PERM;
	}
	if (*code != FILE_NO_PERM)
		*code = CMD_NOT_FOUND;
	free(path);
	return (NULL);
}

void	exec_command(t_shell *shell, int n)
{
	int				i;
	char			**path_array;
	t_command		*cmd;

	i = 0;
	cmd = &shell->tab[n];
	search_absolute_path(shell, n);
	path_array = split_path_var(shell, n);
	if (cmd->error.code != OK)
		return (exec_error(NULL, shell, "malloc"));
	while (path_array[i])
	{
		path_array[i] = test_path(path_array[i], cmd->cmd[0], &cmd->error.code);
		if (cmd->error.code == MALLOC)
			return (exec_error(path_array, shell, "malloc"));
		if (path_array[i])
		{
			execve(path_array[i], cmd->cmd, shell->env);
			return (exec_error(path_array, shell, "execve"));
		}
		i++;
	}
	cmd->error = set_error(cmd->cmd[0], cmd->error.code);
	return (exec_error(path_array, shell, NULL));
}
