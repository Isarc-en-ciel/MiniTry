/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 14:53:33 by iwaslet           #+#    #+#             */
/*   Updated: 2024/09/26 16:13:11 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minitry.h"
//ici on doit conserver les variables d'env uniquement
t_lexer	create_doubleq(char *input, int *position, t_lexer token)
{
	int	l;

	l = 0;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = D_QUOTE;
	token.word = NULL;
	l = check_open_quotes(input, '\"', *position);
	if (l == 0)
		return (token);
	token.word = malloc(sizeof(char) * l);
	if (token.word == NULL)
		return (token);
	token.word = ft_memcpy_plus(token.word, input, *position + 1, l);
	*position = *position + l + 1;
	return (token);
}

t_lexer	create_simpleq(char *input, int *position, t_lexer token)
{
	int	l;

	l = 0;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = QUOTE;
	token.word = NULL;
	l = check_open_quotes(input, '\'', *position);
	if (l == 0)
		return (token);
	token.word = malloc(sizeof(char) * l);
	if (token.word == NULL)
		return (token);
	token.word = ft_memcpy_plus(token.word, input, *position + 1, l);
	*position = *position + l + 1;
	return (token);
}

int	check_open_quotes(char *str, char c, int j)
{
	int	i;

	i = j + 1;
	while (str[i])
	{
		if (str && str[i] == c)
			return (i - j);
		i++;
	}
	return (0);
}

t_lexer	create_word(char *input, int *position, t_lexer token) //attention si des quotes sont ouvertes 'dans un mot'
{
	int	l;
	int	i;

	i = *position;
	l = *position;
	token.is_there_a_space = 0;
	if ((*position > 0) && input[*position - 1] && input[*position - 1] == 32)
		token.is_there_a_space = 1;
	token.type = WORD;
	token.word = NULL;
	while (input[i] && !ft_isspace(input[i]))
		i++;
	l = i - l + 1;
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
	while (i < n - 1)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[start + i];
		i++;
	}
	((unsigned char *)dst)[i] = '\0';
	return (dst);
}
