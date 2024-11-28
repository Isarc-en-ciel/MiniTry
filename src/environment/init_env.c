/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:43:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/25 11:37:25 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*add_env_var(char *str)
{
	char	*new_env_var;

	if (!str)
		return (NULL);
	new_env_var = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_env_var)
		return (NULL);
	ft_memcpy(new_env_var, str, ft_strlen(str));
	return (new_env_var);
}

static char	**init_empty_env(void)
{
	char	**empty_env;

	empty_env = malloc(sizeof(char *) * (2 + 1));
	if (!empty_env)
		return (NULL);
	empty_env[0] = getcwd(NULL, 0);
	if (!empty_env[0])
	{
		free(empty_env);
		return (NULL);
	}
	empty_env[0] = ft_strjoin("PWD=", empty_env[0], S2_MALLOC);
	if (!empty_env[0])
	{
		free(empty_env);
		return (NULL);
	}
	empty_env[1] = ft_strjoin("SHLVL=", "1", NO_MALLOC);
	if (!empty_env[1])
	{
		free_tab_char(empty_env);
		return (NULL);
	}
	empty_env[2] = NULL;
	return (empty_env);
}

static char	**copy_env(char **envp)
{
	char	**new_env;
	int		i;

	new_env = NULL;
	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(*envp) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = add_env_var(envp[i]);
		if (!new_env[i])
		{
			free_tab_char(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**init_env(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = NULL;
	if (!envp || !*envp)
	{
		new_env = init_empty_env();
		if (!new_env)
			exit_error(NULL, "malloc");
		return (new_env);
	}
	new_env = copy_env(envp);
	if (!new_env)
		exit_error(NULL, "malloc");
	return (new_env);
}
