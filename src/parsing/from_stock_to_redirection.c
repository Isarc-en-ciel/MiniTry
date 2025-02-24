/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_stock_to_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:25:28 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/24 16:07:25 by csteylae         ###   ########.fr       */
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

static void	resolve_hd_or_filename(t_redirect *p_redir, t_lexer cmd)
{
	char	*str;

	if (cmd.word)
		str = ft_strdup(cmd.word);
	else
		str = ft_calloc(1, sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	if (p_redir->type == REDIR_HEREDOC)
	{
		p_redir->filename = NULL;
		p_redir->hd_delimiter = str;
		if (cmd.type != WORD)
			p_redir->hd_expansion = false;
		else
			p_redir->hd_expansion = true;
	}
	else
	{
		p_redir->filename = str;
		p_redir->hd_delimiter = NULL;
		p_redir->hd_expansion = false;
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
			resolve_hd_or_filename(&r_array[j], cmd[i]);
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
