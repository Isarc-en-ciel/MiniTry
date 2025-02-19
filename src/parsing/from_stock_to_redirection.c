/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:28 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/19 20:02:03 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_redir_operator(enum e_tokens type)
{
	if (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_HEREDOC
		|| type == REDIR_APP)
	{
		return (true);
	}
	return (false);
}

static int	count_redirection_operator(t_lexer *cmd, int cmd_size)
{
	int	nb_of_redir;
	int	i;

	nb_of_redir = 0;
	i = 0;
	while (i != cmd_size)
	{
		if (is_redir_operator(cmd[i].type))
		{
			if (i == cmd_size)
				return (REDIR_SYNTAX_ERROR);
			else if (!is_redir_operator(cmd[i + 1].type))
				nb_of_redir++;
			else
				return (REDIR_SYNTAX_ERROR);
		}
		i++;
	}
	return (nb_of_redir);
}

static void	resolve_hd_or_filename(t_redirect *p_redir, char *filename)
{
	if (p_redir->type == REDIR_HEREDOC)
	{
		p_redir->filename = NULL;
		p_redir->hd_delimiter = ft_strdup(filename);
		if (!p_redir->hd_delimiter)
			exit(EXIT_FAILURE);
	}
	else
	{
		p_redir->filename = ft_strdup(filename);
		if (!p_redir->filename)
			exit(EXIT_FAILURE);
		p_redir->hd_delimiter = NULL;
	}
}

static t_redirect	*get_array(int array_size, t_lexer *cmd, int cmd_size)
{
	int			i;
	int			j;
	t_redirect	*r_array;

	i = 0;
	j = 0;
	r_array = malloc(sizeof(t_redirect) * array_size);
	if (!r_array)
		return (NULL);
	while (i < cmd_size)
	{
		if (is_redir_operator(cmd[i].type))
		{
			r_array[j].type = cmd[i].type;
			i++;
			resolve_hd_or_filename(&r_array[j], cmd[i].word);
			j++;
		}
		i++;
	}
	return (r_array);
}

t_redir_array	get_redirections(t_lexer *cmd, int cmd_size, int *pstatus)
{
	t_redir_array	redirections;

	redirections.size = count_redirection_operator(cmd, cmd_size);
	if (redirections.size < 0)
	{
		*pstatus = SYNTAX_ERROR;
		return (redirections);
	}
	if (redirections.size == 0)
	{
		redirections.array = NULL;
		return (redirections);
	}
	redirections.array = get_array(redirections.size, cmd, cmd_size);
	return (redirections);
}
