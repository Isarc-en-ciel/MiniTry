/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/02 15:37:41 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

void	set_cwd(t_command *cmd, t_env_list **head)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (!value)
	{
		cmd->error = set_error("getcwd", SYSCALL_ERROR);
		return ;
	}
	update_env(cmd, head, "PWD", value);
	free(value);
	value = NULL;
}

void	change_directory(t_command *cmd, t_env_list **head)
{
	char	*path;

	path = cmd->cmd[1];
	ft_printf("path : %s\n", path);
	set_cwd(cmd, head);
	if (cmd->error.code != OK)
		return ;
	if (!path)
	{
		path = get_env_value(*head, "HOME");
		if (!path)
		{
			ft_putstr_fd("cd : HOME not set\n", STDOUT_FILENO);
			cmd->error = set_error("cd", CD_ERROR);
			return ;
		}
	}
	if (chdir(path) != 0)
	{
		cmd->error = set_error("chdir", SYSCALL_ERROR);
		return ;
	}
	set_cwd(cmd, head);
}

int	ft_cd(char ***envp, t_command *cmd)
{
	int			status;
	t_env_list	*head;

	status = 0;
	head = array_to_list(*envp);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	if (cmd->cmd[1] && cmd->cmd[2])
		return (builtin_error(cmd, cmd->cmd[0], BUILTIN_OPT, NULL));
	change_directory(cmd, &head);
	if (cmd->error.code != OK)
		return (builtin_error(cmd, NULL, 0, &head));
	build_envp(&head, cmd, envp);
	destroy_lst(&head);
	if (cmd->error.code != OK)
		return (FAIL);
	return (SUCCESS);
}
