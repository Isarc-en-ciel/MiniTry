/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_binary_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:15:58 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/06 16:58:24 by csteylae         ###   ########.fr       */
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

static char	*construct_path(char *path, char *cmd_name, t_command *cmd)
{
	char	*slash_cmd;
	char	*full_path;

	slash_cmd = NULL;
	full_path = NULL;
	slash_cmd = ft_strjoin("/", cmd_name, NO_MALLOC);
	if (!slash_cmd)
	{
		cmd->error = set_error("malloc", MALLOC);
		return (NULL);
	}
	full_path = ft_strjoin(path, slash_cmd, S2_MALLOC);
	if (!path)
	{
		cmd->error = set_error("malloc", MALLOC);
		return (NULL);
	}
	return (full_path);
}

static void	update_file_status(enum e_error *code, t_command *cmd)
{
	if (cmd->error.code != CMD_NOT_FOUND)
		*code = cmd->error.code;
}

char	*find_binary_path(t_command *cmd, char **path_array)
{
	int					i;
	enum e_error		file_status;
	char				*path;

	i = 0;
	file_status = CMD_NOT_FOUND;
	path = NULL;
	while (path_array[i])
	{
		path = construct_path(path_array[i], cmd->cmd[0], cmd);
		if (!path)
			return (NULL);
		path = check_path_accessibility(path, cmd);
		if (path)
		{
			return (path);
		}
		update_file_status(&file_status, cmd);
		free(path);
		path = NULL;
		i++;
	}
	cmd->error.code = file_status;
	ft_printf("yup\n");
	return (NULL);
}

char	*get_binary_path(t_shell *sh, int n, t_command *cmd)
{
	char	**path_array;
	char	*path;

	path = NULL;
	path_array = split_path_var(sh, n);
	if (!path_array)
	{
		if (cmd->error.code != MALLOC)
			cmd->error.code = CMD_NOT_FOUND;
		return (NULL);
	}
	path = find_binary_path(cmd, path_array);
	free_tab_char(path_array);
	return (path);
}
