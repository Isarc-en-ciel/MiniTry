/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:34:48 by csteylae          #+#    #+#             */
/*   Updated: 2024/08/01 18:39:49 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static char **get_absolute_path(char *cmd)
{
	char **path;

	path = malloc(sizeof(*path) * 1);
	if (!path)
		return (NULL);
	path[0] = ft_strdup(cmd);
	if (!path[0])
	{
		free(path);
		return (NULL);
	}
	path[1] = NULL;
	return (path);
}

static char **get_path(char **env, char *cmd)
{
	int	i;
	char *path_env;

	if (ft_strchr(cmd, '/'))
		return (get_absolute_path(cmd));
	i = 0;
	path_env = NULL;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	path_env = env[i] + ft_strlen("PATH=");
	return (ft_split(path_env, ':'));
}

static void	exec_error(char **path)
{
	int	i;

	i = 0;
	ft_putstr_fd("error\n", STDERR_FILENO);
	perror("error\n");
	if (path && *path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
	}
	//free data();
	free(path);
	exit(EXIT_FAILURE);
}

void	exec_command(t_data data, int n)
{
	int		i;
	char	**path;

	i = 0;
	path = get_path(data.env, data.tab[n].cmd[0]);
	ft_printf("testtttttttt\n");
	if (!path)
		exec_error(path);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], data.tab[n].cmd[0]);
		if (!path[i])
			exec_error(path);
		if (access(path[i], X_OK) == 0)
		{
			if (execve(path[i], data.tab[n].cmd, data.env) < 0)
				exec_error(path);
		}
		i++;
	}
}
