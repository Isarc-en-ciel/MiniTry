/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/18 15:10:54 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int	ft_cd(char ***env, t_command *cmd)
{
	int			status;
	t_env_list	*head;

	head = array_to_list(*env);
	env_modify_value("OLDPWD", getcwd(NULL, 0), &head);
	status = chdir(cmd->cmd[1]);
	if (status == 0)
	{
		env_modify_value("PWD", getcwd(NULL, 0), &head);
	}
	*env = list_to_array(&head);
	if (!*env)
	{
		return (ft_printf("error malloc occurs the error should be reported\n"));
	}
	return (status);
}
