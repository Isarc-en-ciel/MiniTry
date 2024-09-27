/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:10:58 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/25 15:46:15 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitry.h"

int main(int argc, char **argv, char **envp)
{
	char *hd;
	char *del;
	char *line;
	int	 heredoc[2];

	(void)argc;
	(void)envp;
	hd = argv[1];
	del = argv[2];
	ft_printf("del :%s\n", del);
	line = NULL;
	pipe(heredoc);
	if (!ft_strncmp("lol", "lol", ft_strlen("lol")))
		ft_printf("yup\n");

//	dup2(STDOUT_FILENO, heredoc[WRITE_TO]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(del, line, ft_strlen(line)))
		{
			close(heredoc[READ_FROM]);
			close(heredoc[WRITE_TO]);
			ft_printf("del found youpi\n");
			break;
		}
		if (!line)
		{
			ft_printf("line is null\n");
			break;
		}
		ft_putstr_fd(line, heredoc[WRITE_TO]);
		free(line);
		line = NULL;
	}
	close(heredoc[READ_FROM]);
	close(heredoc[WRITE_TO]);
}
