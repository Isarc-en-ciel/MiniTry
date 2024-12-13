/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/13 19:59:36 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	set_cwd(t_command *cmd, t_env_list **head, char *key)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (!value)
	{
		cmd->error = set_error("getcwd", SYSCALL_ERROR);
		return ;
	}
	update_env(cmd, head, key, value);
	free(value);
	value = NULL;
}

char	*get_path(t_env_list *head, char *str, t_command *cmd)
{
	char		*path;

	path = str;
	if (!str)
	{
		path = get_env_value(head, "HOME");
		if (!path)
		{
			cmd->error = set_error(NULL, FAIL);
			ft_putstr_fd("cd: HOME not set\n", STDOUT_FILENO);
			return (NULL);
		}
	}
	if (key_found("-", str))
	{
		path = get_env_value(head, "OLDPWD");
		if (!path || !path[0])
		{
			cmd->error = set_error(NULL, FAIL);
			ft_printf("cd: OLDPWD not set\n");
		}
	}
	path = ft_strdup(path);
	return (path);
}

void	change_directory(t_command *cmd, t_env_list **head)
{
	char	*path;
	int		status;

	status = 0;
	path = get_path(*head, cmd->cmd[1], cmd);
	path = ft_strdup(path);
	if (!path)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	set_cwd(cmd, head, "OLDPWD");
	if (cmd->error.code != OK)
	{
		free(path);
		return ;
	}
	status = chdir(path);
	if (status != SUCCESS)
		cmd->error = set_error("cd", status);
	set_cwd(cmd, head, "PWD");
	free(path);
}

static int	rebuild_envp(char ***envp, t_command *cmd, t_env_list **head)
{
	build_envp(head, cmd, envp);
	destroy_lst(head);
	if (cmd->error.code != OK)
		return (FAIL);
	return (SUCCESS);
}

int	ft_cd(char ***envp, t_command *cmd, int exit_status)
{
	t_env_list	*head;

	head = NULL;
	if (!init_env_list(&head, cmd, *envp))
		return (FAIL);
	if (cmd->cmd[1] && cmd->cmd[2])
		return (builtin_error(cmd, cmd->cmd[0], BUILTIN_OPT, NULL));
	change_directory(cmd, &head);
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, 0, &head));
	exit_status = rebuild_envp(envp, cmd, &head);
	return (exit_status);
}
