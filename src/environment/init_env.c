/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:43:07 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 17:16:51 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*add_env_var(char *str)
{
	char *new_env_var;

	if (!str)
		return (NULL);
	new_env_var = calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_env_var)
		return (NULL); //need to manage error
	ft_memcpy(new_env_var, str, ft_strlen(str));
	return (new_env_var);
}

char	**init_env(char **envp)
{
	char **new_env;
	int	i;

	i = 0;
	if (!envp || !*envp)
		return (NULL);
	while (envp[i])
		i++;
	new_env = malloc(sizeof(*envp) * (i + 1));
	if (!new_env)
	{
		ft_putstr_fd("error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		new_env[i] = add_env_var(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
