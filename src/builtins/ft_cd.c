/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/05 11:46:34 by csteylae         ###   ########.fr       */
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
	int		status;

	path = cmd->cmd[1];
	status = 0;
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
	status = chdir(path);
	if (status != SUCCESS)
		cmd->error = set_error("cd", status);
	set_cwd(cmd, head);
}

int	ft_cd(char ***envp, t_command *cmd, int exit_status)
{
	t_env_list	*head;

	(void)exit_status;
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
