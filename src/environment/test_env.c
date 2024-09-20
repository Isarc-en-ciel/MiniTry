/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:09:39 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/20 11:43:40 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

static int	count_nb_of_cmd(char *input)
{
	int	i = 1; //we suppose there is at leat 1 command

	while (*input)
	{
		if (*input == '|')
			i++;
		input++;
	}
	return (i);
}

static void	set_all_members_to_NULL(t_command *tab, int size)
{
	int	i = 0;

	while (i != size)
	{
		tab[i].cmd = NULL;
		tab[i].in = NULL;
		tab[i].out = NULL;
		tab[i].append = NULL;
		tab[i].heredoc = NULL;
		i++;
	}
}

static void parse_cmd(t_shell *shell, t_command *tab, char *input)
{
	int i;
	char **input_split;
	(void)shell;

	i = 0;
	input_split = ft_split(input, '|');
	while(input_split[i])
	{
		tab[i].cmd = ft_split(input_split[i], ' ');
		i++;
	}
	free_tab_char(input_split);
}

static	t_command *pseudo_parsing(t_shell *shell, char *input)
{
	t_command *tab;
	int	nb_of_cmd;

	nb_of_cmd = count_nb_of_cmd(input);
	shell->tab_size = nb_of_cmd;
//	ft_printf("nb of cmd : %d\n", shell->tab_size);
	tab	= malloc(sizeof(*tab) * (nb_of_cmd));
	if (!tab)
		exit_error(shell, "malloc");
	set_all_members_to_NULL(tab, nb_of_cmd);
	parse_cmd(shell, tab, input);
	return (tab);
}

void	test_env(t_shell *shell, char *input)
{
	exec_cd("src/execution");
	shell->tab = pseudo_parsing(shell, input);
	exec_prompt(shell);
}

void	ft_print_cmd(t_shell *shell)
{
	int	i = 0;
	int	j = 0;

	while (i != shell->tab_size)
	{
		while (shell->tab[i].cmd[j] != NULL)
		{
			ft_printf("%s\n", shell->tab[i].cmd[j]);
			j++;
		}
		j = 0;
		i++;
	}
}
