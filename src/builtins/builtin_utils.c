/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:11:33 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/21 13:10:19 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	init_env_list(t_env_list **head, t_command *cmd, char **env)
{
	*head = NULL;
	*head = array_to_list(env);
	if (!*head)
	{
		if (cmd)
			cmd->error = set_error("malloc", MALLOC);
		else
			perror("malloc");
		return (false);
	}
	return (true);
}

int	builtin_error(t_command *cmd, char *s, enum e_error code, t_env_list **head)
{
	if (cmd)
	{
		if (cmd->error.code == SUCCESS)
			cmd->error = set_error(s, code);
		else
			perror(s);
	}
	if (head && *head)
		destroy_lst(head);
	return (FAIL);
}

void	build_envp(t_env_list **head, t_command *cmd, char ***envp)
{
	char	**new_envp;

	new_envp = list_to_array(head);
	if (!new_envp)
	{
		ft_printf("cannot list to array :(\n");
		builtin_error(cmd, "malloc", MALLOC, head);
	}
	free_tab_char(*envp);
	*envp = new_envp;
}

static void	print_not_valid_identifier(char *str, t_command *cmd)
{
	ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
	ft_putstr_fd(" : '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

bool	is_key_format(t_command *cmd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[0] != '_' && !ft_isalpha(str[0]))
		{
			print_not_valid_identifier(str, cmd);
			return (false);
		}
		else if (i > 0)
		{
			if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			{
				print_not_valid_identifier(str, cmd);
				return (false);
			}
		}
		i++;
	}
	return (true);
}
