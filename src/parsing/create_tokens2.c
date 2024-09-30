/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:51:15 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/30 13:34:20 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

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
