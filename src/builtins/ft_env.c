/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:59:48 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/04 15:42:21 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_print_env(t_env_list *head, int fd)
{
	t_env_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->is_init)
		{
			ft_putstr_fd(tmp->key, fd);
			ft_putstr_fd("=", fd);
			if (tmp->is_init && tmp->value[0] == '\0')
			{
				ft_putstr_fd("""\n", fd);
			}
			else
			{
				ft_putstr_fd(tmp->value, fd);
				ft_putstr_fd("\n", fd);
			}
		}
		tmp = tmp->next;
	}
}

static int	update_underscore(t_env_list **head, char ***envp, t_command *cmd)
{
	if (!update_env(head, "_", "./src/builtins/ft_env.c"))
		return (FAIL);
	build_envp(head, cmd, envp);
	if (cmd->error.code != SUCCESS)
		return (FAIL);
	return (SUCCESS);
}

int	ft_env(t_shell *sh, t_command *cmd)
{
	t_env_list	*head;
	int			fd;

	head = NULL;
	fd = STDOUT_FILENO;
	if (cmd->fd_out != NO_REDIR)
		fd = cmd->fd_out;
	if (!init_env_list(&head, cmd, sh->env))
		return (FAIL);
	if (cmd->cmd[1])
	{
		ft_putstr_fd("env : '", STDOUT_FILENO);
		ft_putstr_fd(cmd->cmd[1], STDOUT_FILENO);
		ft_putstr_fd("' no such file or directory\n", STDOUT_FILENO);
		return (builtin_error(cmd, NULL, FAIL, &head));
	}
	if (update_underscore(&head, &sh->env, cmd) == FAIL)
		sh->exit_status = builtin_error(cmd, NULL, 0, &head);
	else
	{
		sh->exit_status = SUCCESS;
		ft_print_env(head, fd);
		destroy_lst(&head);
	}
	return (sh->exit_status);
}
