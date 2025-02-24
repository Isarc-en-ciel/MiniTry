/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:08:05 by csteylae          #+#    #+#             */
/*   Updated: 2025/02/24 18:08:10 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	is_cmd_args(t_lexer *cmd, int i)
{
	if (i == 0 && !is_redir_operator(cmd[i].type))
		return (true);
	else if (i > 0 && !is_redir_operator(cmd[i - 1].type)
		&& !is_redir_operator(cmd[i].type))
	{
		return (true);
	}
	else
		return (false);
}

static int	get_cmd_args_size(t_lexer *cmd, int cmd_size)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i != cmd_size)
	{
		if (is_cmd_args(cmd, i))
			len++;
		i++;
	}
	return (len);
}

static char	*copy_word(char *word)
{
	char	*str;

	str = NULL;
	if (word)
		str = ft_strdup(word);
	else if (word == NULL)
		str = ft_calloc(1, sizeof(char));
	if (!str)
		exit(EXIT_FAILURE);
	return (str);
}

char	**get_cmd_args(t_lexer *cmd, int cmd_size)
{
	int		i;
	int		len;
	char	**cmd_args;

	i = 0;
	len = 0;
	if (get_cmd_args_size(cmd, cmd_size) == 0)
		return (NULL);
	cmd_args = malloc(sizeof(char *) * (get_cmd_args_size(cmd, cmd_size) + 1));
	if (!cmd_args)
		exit_error(NULL, "malloc");
	while (i != cmd_size)
	{
		if (is_cmd_args(cmd, i))
		{
			cmd_args[len] = copy_word(cmd[i].word);
			len++;
		}
		i++;
	}
	cmd_args[len] = NULL;
	return (cmd_args);
}
