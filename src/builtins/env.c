/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 17:03:21 by csteylae          #+#    #+#             */
/*   Updated: 2024/07/26 17:07:41 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitry.h"

void	exec_env(char *str, char **envp)
{
	int	i;

	i = 0;
	if (!ft_strncmp("env", str, ft_strlen("env")))
	{
		while (envp[i])
		{
			printf("%s\n", envp[i]);
			i++;
		}
	}
}
