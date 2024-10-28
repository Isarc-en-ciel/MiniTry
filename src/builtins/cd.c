/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/28 12:16:10 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h" 

int	ft_cd(char ***env, char **args)
{
	char		*current_dir;
	int			status;
	t_env_list	*head;
	t_env_list	*pwd_node;

	head = array_to_list(*env);
	pwd_node = find_node("OLDPWD", head);
	if (!pwd_node)
	{
		return (ft_printf("OLDPWD NOT FOUND\n"));
	}
	pwd_node->value = getcwd(NULL, 0);
	status = chdir(args[1]);
	if (status == 0)
	{
		current_dir = getcwd(NULL, 0);
		pwd_node = find_node("PWD", head);
		if (!pwd_node)
		{
			ft_printf("PWD_VAR not found\n");
			return (EXIT_FAILURE);
		}
		free(pwd_node->value);
		pwd_node->value = current_dir;
//		ft_print_list(head);
	}
	*env = list_to_array(&head);
	if (!*env)
	{
		return (ft_printf("error malloc occurs the error should be reported\n"));
	}
	return (status);
}
