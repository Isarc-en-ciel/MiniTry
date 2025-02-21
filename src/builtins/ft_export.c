/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 14:31:33 by csteylae         ###   ########.fr       */
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
	if (str[0] == '=')
		i++;
	key = ft_calloc(i + 1, sizeof(char));
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
	if (*value == '\0')
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
		if (is_key_format(cmd, key))
		{
			*exit_status = SUCCESS;
			value = get_value(cmd->cmd[i]);
			if (!update_env(head, key, value))
			{
				cmd->error = set_error(NULL, MALLOC);
				return ;
			}
		}
		else
			*exit_status = FAIL;
		free(key);
		i++;
	}
}

int	ft_export(t_shell *sh, t_command *cmd)
{
	t_env_list	*head;

	head = NULL;
	if (!init_env_list(&head, cmd, sh->env))
		return (FAIL);
	if (!cmd->cmd[1])
	{
		export_without_arg(&head, cmd);
		destroy_lst(&head);
		return (SUCCESS);
	}
	export_var(&head, cmd, &sh->exit_status);
	if (cmd->error.code != SUCCESS)
		return (builtin_error(cmd, NULL, 0, &head));
	build_envp(&head, cmd, &sh->env);
	destroy_lst(&head);
	if (cmd->error.code != SUCCESS)
		sh->exit_status = FAIL;
	return (sh->exit_status);
}
