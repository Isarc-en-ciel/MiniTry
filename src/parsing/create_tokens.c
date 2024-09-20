/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:53:33 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/19 20:05:55 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"

t_lexer	create_pipe(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.type = PIPE;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	return (token);
}

t_lexer	create_redirect_in(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = REDIR_IN;
	position++;
	if (input[*position + 1] == '<')
	{
		token.type = REDIR_HEREDOC;
		position++;
	}
	return (token);
}

t_lexer	create_redirect_out(char *input, int *position, t_lexer token)
{
	token.word = NULL;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = REDIR_OUT;
	position++;
	if (input[*position + 1] == '>')
	{
		token.type = REDIR_APP;
		position++;
	}
	return (token);
}

t_lexer	create_doubleq(char *input, int *position, t_lexer token) //ici on doit conserver les variables d'env uniquement
{
	int	l;

	l = 0;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = D_QUOTE;
	token.word = NULL;
	l = check_open_quotes(input, '\"', *position);
	if (l == 0)
		return (token);
	token.word = malloc(sizeof(char) * l);
	if (token.word == NULL)
		return (token);
	token.word = ft_memcpy_plus(token.word, input, *position, l);
	*position = *position + l;
	return (token);
}

t_lexer	create_simpleq(char *input, int *position, t_lexer token)
{
	int	l;

	l = 0;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = QUOTE;
	token.word = NULL;
	l = check_open_quotes(input, '\'', *position);
	if (l == 0)
		return (token);
	token.word = malloc(sizeof(char) * l);
	if (token.word == NULL)
		return (token);
	token.word = ft_memcpy_plus(token.word, input, *position, l);
	*position = *position + l;
	return (token);
}

int	check_open_quotes(char *str, char c, int j)
{
	int	i;

	i = j;
	while (str++)
	{
		if (str[i] == c)
			return (i - j);
		i++;
	}
	return (0);
}

t_lexer	create_word(char *input, int *position, t_lexer token)
{
	int	l;
	int	i;

	i = *position;
	l = *position;
	token.is_there_a_space = 0;
	if (input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = QUOTE;
	token.word = NULL;
	while (input[i] && ft_isspace(input[i]))
		i++;
	l = i - l;
	token.word = malloc(sizeof(char) * l);
	if (token.word == NULL)
		return (token);
	token.word = ft_memcpy_plus(token.word, input, *position, l);
	*position = *position + l;
	return (token);
}

void	*ft_memcpy_plus(void *dst, const void *src, int start, int n)
{
	int	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[start + i];
		i++;
	}
	return (dst);
}
