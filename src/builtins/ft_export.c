/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:33:53 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/12 13:00:46 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* The return status is zero unless an invalid option is supplied, one of the 
names is not a valid shell variable name, or -f is supplied with a name that is not a shell function. 
*/

static char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	key = NULL;
	while (str[i] && str[i] != '=')
		i++;
//	if (!str[i])
//		return (str);
	key = calloc(i, sizeof(char) + 1);
	if (!key)
		return (NULL);
	ft_memcpy(key, str, i);
	return (key);
}

int	ft_export(char ***env, t_command *cmd, int exit_status)
{
	t_env_list	*head;
	char		*key;
	char		*value;
	int			i;

	i = 1;
	head = array_to_list(*env);
	if (!head)
		return (builtin_error(cmd, "malloc", MALLOC, NULL));
	if (!cmd->cmd[1])
	{
		print_all_env_var(&head);
		return (SUCCESS);
	}
	while (cmd->cmd[i])
	{
		key = get_key(cmd->cmd[i]);
		if (!key)
			return (builtin_error(cmd, "malloc", MALLOC, &head));
		if (!is_key_format(cmd, key))
		{
			exit_status = FAIL;
			i++;
			continue ;
		}
		if (!ft_strchr(cmd->cmd[i], '='))
			update_env(cmd, &head, key, NULL);
		else
		{
			value = ft_strchr(cmd->cmd[i], '=') + 1;
			if (value[0])
				value = "";
			update_env(cmd, &head, key, value);
		}
		if (cmd->error.code != 0)
		{
			return (builtin_error(cmd, "malloc", MALLOC, &head));
		}
		free(key);
		key = NULL;
		exit_status = SUCCESS;
		i++;
	}
	build_envp(&head, cmd, env);
	destroy_lst(&head);
	return (exit_status);
}
