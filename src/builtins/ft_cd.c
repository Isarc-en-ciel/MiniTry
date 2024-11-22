/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/22 18:29:53 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	create_new_env(t_env_list **head, char *key, char *value, t_command *cmd)
{
	t_env_list	*elem;

	elem = new_env_list(key, value);
	if (!elem)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	lst_addback(head, elem);
}

void	update_env(t_command *cmd, t_env_list **head, char *key, char *value)
{
	t_env_list	*elem;

	elem = get_env(key, *head);
	if (!elem)
		create_new_env(head, key, value, cmd);
	else
		replace_env(key, value, head, cmd);
}

void	change_directory(t_command *cmd, t_env_list **head)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (!value)
	{
		cmd->error = set_error("getcwd", SYSCALL_ERROR);
		return ;
	}
	update_env(cmd, head, "OLDPWD", value);
	free(value);
	if (cmd->error.code != OK)
		return ;
	if (chdir(cmd->cmd[1]) != 0)
	{
		cmd->error = set_error("chdir", SYSCALL_ERROR);
		return ;
	}
	value = getcwd(NULL, 0);
	if (!value)
	{
		cmd->error = set_error("getcwd", SYSCALL_ERROR);
		return ;
	}
	update_env(cmd, head, "PWD", value);
	free(value);
}

int	ft_cd(char ***envp, t_command *cmd)
{
	int			status;
	t_env_list	*head;

	status = 0;
	head = NULL;
	if (cmd->cmd[2])
		return (builtin_error(cmd, cmd->cmd[0], BUILTIN_OPT, NULL));
	if (*envp)
	{
		head = array_to_list(*envp);
		if (!head)
			return (builtin_error(cmd, "malloc", MALLOC, NULL));
	}
	change_directory(cmd, &head);
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, 0, &head));
	build_envp(&head, cmd, envp);
	if (cmd->error.code != OK)
		status = 1;
	destroy_lst(&head);
	return (status);
}
