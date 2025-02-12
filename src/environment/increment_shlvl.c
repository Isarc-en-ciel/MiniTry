/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:27:48 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/01 14:10:12 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	update_lvl(char *value)
{
	int	lvl;

	lvl = 0;
	lvl = ft_atoi(value);
	lvl++;
	if (lvl >= 1000 || lvl < 0)
		lvl = 0;
	return (lvl);
}

static void	update_shlvl(t_env_list *shlvl)
{
	int	lvl_incr;

	lvl_incr = update_lvl(shlvl->value);
	free(shlvl->value);
	shlvl->value = NULL;
	shlvl->value = ft_itoa(lvl_incr);
	if (!shlvl->value)
		shlvl->value = NULL;
}

void	incr_shlvl(t_shell *sh)
{
	t_env_list	*head;
	t_env_list	*shlvl;

	if (!sh)
		return ;
	head = array_to_list(sh->env);
	if (!head)
		exit_error(sh, "malloc");
	shlvl = get_env("SHLVL", &head);
	if (!shlvl)
	{
		shlvl = new_env_list("SHLVL", "1", true);
		lst_addback(&head, shlvl);
	}
	else
	{
		update_shlvl(shlvl);
		if (!shlvl->value)
			exit_error(sh, "malloc");
	}
	build_envp(&head, NULL, &sh->env);
	destroy_lst(&head);
	if (!sh->env)
		exit_error(sh, NULL);
}
