/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/05 17:36:21 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_key(char *str, t_command *cmd)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	if (ft_strnstr(str, "+=", ft_strlen(str)))
	{
		while (str[i] && str[i] != '+')
			i++;
	}
	else
	{
		while (str[i] && str[i] != '=')
			i++;
	}
	if (i == 0)
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

static char	*concatenate(t_env_list *var, char *value, t_command *cmd, bool *p)
{
	char	*concatenated_val;

	concatenated_val = NULL;
	value += 2;
	if (!var)
		return (value);
	if (!var->value && value)
		return (value);
	else if (var->value && !value)
		return (var->value);
	else
	{
		concatenated_val = ft_strjoin(var->value, value, NO_MALLOC);
		if (!concatenated_val)
		{
			cmd->error = set_error("malloc", MALLOC);
			return (NULL);
		}
		*p = true;
		return (concatenated_val);
	}
}

static void	get_value(t_command *cmd, char *arg, t_env_list **head, char *key)
{
	char		*value;
	t_env_list	*var;
	bool		should_freed;

	var = get_env(key, head);
	value = ft_strnstr(arg, "+=", ft_strlen(arg));
	should_freed = false;
	if (value)
	{
		value = concatenate(var, value, cmd, &should_freed);
		if (cmd->error.code != SUCCESS)
			return ;
	}
	else
	{
		value = ft_strchr(arg, '=');
		if (value)
			value += 1;
	}
	if (var && !ft_strchr(arg, '='))
		return ;
	if (!update_env(head, key, value))
		cmd->error = set_error("malloc", MALLOC);
	if (should_freed)
		free(value);
}

static void	export_var(t_env_list **head, t_command *cmd, int *exit_status)
{
	int		i;
	char	*key;

	i = 1;
	while (cmd->cmd[i])
	{
		key = get_key(cmd->cmd[i], cmd);
		if (!key)
			return ;
		if (is_key_format(cmd, key))
		{
			*exit_status = SUCCESS;
			get_value(cmd, cmd->cmd[i], head, key);
			if (cmd->error.code != SUCCESS)
				return ;
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
		if (!head)
			return (SUCCESS);
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
