/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:53:33 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/14 17:28:09 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_lexer	create_pipe(char *input, int position, t_lexer token)
{
    token.word = NULL;
    token.type = PIPE;
    token.isthereaspace = 0;
    if (input[position - 1] && input[position - 1] == 32)
        token.isthereaspace = 1;
	return (token);
}

t_lexer create_redirect_in(char *input, int position, t_lexer token)
{
	token.word = NULL;
    token.isthereaspace = 0;
	if (input[position - 1] && input[position - 1] == 32)
        token.isthereaspace = 1;
	token.type = REDIR_IN;
	if (input[position + 1] == '<')
		token.type = REDIR_HEREDOC;
	return (token);
}

t_lexer create_redirect_out(char *input, int position, t_lexer token)
{
	token.word = NULL;
    token.isthereaspace = 0;
	if (input[position - 1] && input[position - 1] == 32)
        token.isthereaspace = 1;
	token.type = REDIR_OUT;
	if (input[position + 1] == '>')
		token.type = REDIR_APP;
	return (token);
}

t_lexer	create_doubleq()
{
	/*check charactere precedent pas un espace
	boucle while separee pour compter longueur (erreur ou si quotes pqs fermes ?)
	allouer memoire mot
	copier mot
	return token*/
}
