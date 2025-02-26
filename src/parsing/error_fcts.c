/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fcts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:06:42 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/26 13:32:26 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	error_fct(t_darray *tab, int i)
{
	if (i == 1)
		write (1, "syntax error\n", 13);
	if (i == 0)
	{
		free_final_array(tab);
		exit (EXIT_FAILURE);
	}
	return (0);
}

t_stock	*error_return(t_darray *tokens, int i, t_shell *shell)
{
	if (tokens)
	{
		free_final_array(tokens);
	}
	if (i == 1)
	{
		shell->exit_status = 2;
		write (1, "syntax error\n", 13);
	}
	if (i == 2)
	{
		shell->exit_status = 1;
		write (1, "too many pipes\n", 15);
	}
	if (i == 0)
		exit (EXIT_FAILURE);
	return (NULL);
}

t_command	*error_parsing(t_stock *tab, int i, t_shell *shell)
{
	if (i == 1)
	{
		shell->exit_status = 2;
		write (1, "syntax error\n", 13);
	}
	if (tab)
		free_second_degree_tab(tab, tab[0].nbr_cmd);
	if (i == 0)
		exit (EXIT_FAILURE);
	return (NULL);
}

int	make_new_cmd(t_lexer *cmd, t_lexer **new_cmd, int nbr_elem)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < nbr_elem)
	{
		if (cmd[i].is_there_a_space != -1)
		{
			if (copy_token(cmd[i], &(new_cmd[0][j])) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	change_type(t_lexer	*joined_token, t_lexer added_token)
{
	if (joined_token->type == D_QUOTE)
		return (0);
	joined_token->type = WORD;
	if (added_token.type == D_QUOTE || added_token.type == QUOTE)
		joined_token->type = D_QUOTE;
	return (0);
}
