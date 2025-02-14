/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:51:15 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/14 12:12:08 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
// a partir de <<< ou >>> syntax error
t_lexer	create_pipe(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.type = PIPE;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	(*position)++;
	return (token);
}

t_lexer	create_redirect_in(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = REDIR_IN;
	(*position)++;
	if (input[*position] && input[*position] == '<')
	{
		token.type = REDIR_HEREDOC;
		(*position)++;
	}
	return (token);
}

t_lexer	create_redirect_out(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = REDIR_OUT;
	(*position)++;
	if (input[*position] == '>')
	{
		token.type = REDIR_APP;
		(*position)++;
	}
	return (token);
}

int	is_delimiter(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\"' || c == '\'')
		return (1);
	return (0);
}
