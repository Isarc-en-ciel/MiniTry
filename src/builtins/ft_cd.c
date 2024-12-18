/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/18 17:28:11 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

/* if errno == ENOENT we should let chdir continue to work in order to find an
   existent directory. 
   So this error should not stop the workflow such as a malloc
   error 
  */

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
	return (path);
}

void	set_cwd(t_command *cmd, t_env_list **head, char *key)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (!value && errno != ENOENT)
	{
		cmd->error = set_error("getcwd:", SYSCALL_ERROR);
		return ;
	}
	else if (!value && errno == ENOENT)
	{
		if (key_found("PWD", key))
		{
			cmd->error = set_error(NOENT_PERROR, ENOENT);
		}
		else
		{
			cmd->error = set_error(NULL, ENOENT);
		}
		return ;
	}
	update_env(cmd, head, key, value);
	free(value);
	value = NULL;
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
	if (cmd->error.code != OK && cmd->error.code != ENOENT)
	{
		free(path);
		return ;
	}
	status = chdir(path);
	free(path);
	if (status != SUCCESS && cmd->error.code != ENOENT)
	{
		cmd->error = set_error("cd", status);
		return ;
	}
	set_cwd(cmd, head, "PWD");
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
	if (cmd->error.code != OK && cmd->error.code != ENOENT)
		return (builtin_error(cmd, NULL, 0, &head));
	exit_status = rebuild_envp(envp, cmd, &head);
	return (exit_status);
}
