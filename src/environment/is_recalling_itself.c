/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_recalling_itself.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 13:41:28 by csteylae          #+#    #+#             */
/*   Updated: 2024/12/03 14:20:21 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	incr_shlvl(t_shell *sh, int n)
{
	t_env_list	*head;
	char		*shlvl_val;
	int			incr;

	head = array_to_list(sh->env);
	shlvl_val = NULL;
	if (!head)
	{
		sh->tab[n].error = set_error("malloc", MALLOC);
		return ;
	}
	shlvl_val = get_env_value(head, "SHLVL");
	if (shlvl_val)
	{
		incr = ft_atoi(shlvl_val);
		incr++;
		shlvl_val = ft_itoa(incr);
		if (!shlvl_val)
		{
			sh->tab[n].error = set_error("malloc", MALLOC);
			return ;
		}
	}
	else
		shlvl_val = "1";
	update_env(&sh->tab[n], &head, "SHLVL", shlvl_val); 
}

void	check_is_recalling(t_shell *sh, int n)
{
	_NSGetExecutablePath

}
