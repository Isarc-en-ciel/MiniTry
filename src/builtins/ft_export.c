/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 15:11:22 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_key(char *str, t_command *cmd)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=')
		i++;
	key = calloc(i, sizeof(char) + 1);
	if (!key)
	{
		cmd->error = set_error("malloc", MALLOC);
		return (NULL);
	}
	ft_memcpy(key, str, i);
	return (key);
}

static char	*get_value(char *str)
{
	char	*value;

	value = ft_strchr(str, '=');
	if (!value)
		return (NULL);
	value = value + 1;
	if (value[0] == '\0')
		return ("");
	return (value);
}

static void	export_var(t_env_list **head, t_command *cmd, int *exit_status)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (cmd->cmd[i])
	{
		key = get_key(cmd->cmd[i], cmd);
		if (!key)
			return ;
		if (!is_key_format(cmd, key))
		{
			*exit_status = FAIL;
			i++;
			continue ;
		}
		value = get_value(cmd->cmd[i]);
		if (!update_env(head, key, value))
		{
			cmd->error = set_error(NULL, MALLOC);
			return ;
		}
		free(key);
		*exit_status = SUCCESS;
		i++;
	}
}

int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	t_env_list	*head;

	head = NULL;
	if (!init_env_list(&head, cmd, *env))
		return (FAIL);
	if (!cmd->cmd[1])
	{
		export_without_arg(&head, cmd);
		destroy_lst(&head);
		return (SUCCESS);
	}
	export_var(&head, cmd, &exit_status);
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, 0, &head));
	build_envp(&head, cmd, env);
	destroy_lst(&head);
	if (cmd->error.code != OK)
		exit_status = FAIL;
	return (exit_status);
}
