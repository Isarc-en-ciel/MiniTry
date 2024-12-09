/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/09 12:26:23 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* The return status is zero unless an invalid option is supplied, one of the 
names is not a valid shell variable name, or -f is supplied with a name that is not a shell function. 
*/

int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	(void)exit_status;
	int	i;

	i = 0;
	head = array_to_list(*env);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	if (!cmd->cmd[1])
	{
		print_all_env_var(&head);
		return (SUCCESS);
	}
	// check value passed to export
	// if value is valid check if env exist
	// if env exists overwrite it 
	// if value doesnt exist create it
	// if multiple values are passed launch the process for every arg
	// if an error occurs (for ex a key isnt correct, report the error but continue to export other arg. 
	// if the last key exported is correct return 0 
	// if the arg isnt correct return 1
	// add it
	return (SUCCESS);
}


