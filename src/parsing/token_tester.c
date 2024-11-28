/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:09:08 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/28 16:12:17 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_token_tab(t_darray *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->actual_size)
	{
		ft_printf("Token has %d space, and has word %s, and has type ",
			cmd->content[i].is_there_a_space, cmd->content[i].word);
		ft_print_redir_type(cmd->content[i].type);
		ft_printf("\n");
		i++;
	}
	return (0);
}

void	ft_print_redir_type(enum e_tokens token)
{
	if (token == REDIR_IN)
		ft_printf("REDIR_IN");
	else if (token == REDIR_OUT)
		ft_printf("REDIR_OUT");
	else if (token == REDIR_APP)
		ft_printf("REDIR_APP");
	else if (token == REDIR_HEREDOC)
		ft_printf("REDIR_HEREDOC");
	else if (token == WORD)
		ft_printf("WORD");
	else if (token == PIPE)
		ft_printf("PIPE");
	else if (token == D_QUOTE)
		ft_printf("D_QUOTE");
	else if (token == QUOTE)
		ft_printf("QUOTE");
}

int	print_stock_tab(t_stock *tab, int cmds)
{
	int	i;
	int	j;

	i = 0;
	while (i < cmds)
	{
		j = 0;
		while (j < tab[i].nbr_elem)
		{
			ft_printf("token : %s\nwith space: %d\nwith type : ",
				tab[i].cmd[j].word, tab[i].cmd[j].is_there_a_space);
			ft_print_redir_type(tab[i].cmd[j].type);
			ft_printf("\n");
			ft_printf("We have %d commands\n", tab[i].nbr_cmd);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	return (0);
}
