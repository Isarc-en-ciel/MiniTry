/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:58:09 by csteylae          #+#    #+#             */
/*   Updated: 2025/03/03 16:58:39 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_hd_expansion(char **line, int fd, t_shell *sh, t_redirect *r)
{
	char	*line_to_exp;

	line_to_exp = NULL;
	if (line && *line && ft_strchr(*line, '$') && r->hd_expansion == true)
	{
		line_to_exp = ft_calloc(ft_strlen(*line), sizeof(char));
		if (!line_to_exp)
		{
			free(line);
			close(fd);
			exit_error(sh, "ft_calloc");
		}
		ft_memcpy(line_to_exp, *line, ft_strlen(*line) - 1);
		free(*line);
		expand_var(sh, &line_to_exp);
		*line = ft_strjoin(line_to_exp, "\n", S1_MALLOC);
		if (!*line)
		{
			close(fd);
			exit_error(sh, "ft_calloc");
		}
	}
	return ;
}
