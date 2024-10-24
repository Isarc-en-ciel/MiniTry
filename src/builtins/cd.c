/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:23:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/24 15:26:20 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h" 

int	ft_strnlen(char *str, char c)
{
	int	i = 0;
	while (str[i] != c)
		i++;
	return i;
}
int	ft_cd(char **args)
{
	(void)args;
	ft_printf("this is cd builtin !\n");
	return (0);
}
