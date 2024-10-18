/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_enum.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:02:51 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/18 12:43:46 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * An enum to identify the different type of redirection that can affect a command
 *
 * REDIR_IN :	<
 * REDIR_OUT:	>	
 * REDIR_HEREDOC : <<
 * REDIR_APPEND :	>>
 */
enum e_tokens {
    PIPE = 1,
    QUOTE,
    D_QUOTE,
    WORD,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APP,
    REDIR_HEREDOC
};

enum e_builtin {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

enum e_error {
	OK,
	OPEN_FILE,
	FILE_NO_EXIST,
	FILE_NO_PERM,
	CMD_NOT_FOUND,
	FORK,
	MALLOC
};

enum {
	NO_REDIR = -1,
	READ_FROM = 0,
	WRITE_TO = 1
};

# define HEREDOC_FILE "/Users/csteylae/goinfre/minishell_heredoc"
