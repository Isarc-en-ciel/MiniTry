/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:53:15 by csteylae          #+#    #+#             */
/*   Updated: 2024/11/27 18:57:56 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand_exit_status(char **retp, int exit_status)
{
	char	*var;

	var = ft_itoa(exit_status);
	if (!var)
	{
		free(*retp);
		*retp = NULL;
		return (-1);
	}
	*retp = update_expanded_value(*retp, var, ft_strlen(var));
	if (!*retp)
		return (0);
	return (2);
}
