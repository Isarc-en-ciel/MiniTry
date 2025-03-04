/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/04 15:33:13 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

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
	return (ft_strdup(path));
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
			cmd->error = set_error(NOENT_PERROR, ENOENT);
		else
			cmd->error = set_error(NULL, ENOENT);
		return ;
	}
	if (!update_env(head, key, value))
		cmd->error = set_error(NULL, MALLOC);
	free(value);
	value = NULL;
}

void	change_directory(t_command *cmd, t_env_list **head)
{
	char	*path;
	int		status;

	status = 0;
	path = get_path(*head, cmd->cmd[1], cmd);
	if (!path)
	{
		cmd->error = set_error("malloc", MALLOC);
		return ;
	}
	set_cwd(cmd, head, "OLDPWD");
	if (cmd->error.code != SUCCESS && cmd->error.code != ENOENT)
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

int	ft_cd(t_shell *sh, t_command *cmd)
{
	t_env_list	*head;

	head = NULL;
	if (!init_env_list(&head, cmd, sh->env))
		return (FAIL);
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDOUT_FILENO);
		return (builtin_error(cmd, NULL, FAIL, &head));
	}
	change_directory(cmd, &head);
	if (cmd->error.code != SUCCESS && cmd->error.code != ENOENT)
		return (builtin_error(cmd, NULL, 0, &head));
	build_envp(&head, cmd, &sh->env);
	if (cmd->error.code != SUCCESS)
	{
		destroy_lst(&head);
		return (FAIL);
	}
	destroy_lst(&head);
	return (SUCCESS);
}
