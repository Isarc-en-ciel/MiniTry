/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_enum.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:02:51 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/24 13:29:18 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_ENUM_H

# define MINITRY_ENUM_H

/**
 * An enum to identify the different type of redirection that can affect a command
 *
 * REDIR_IN :	<
 * REDIR_OUT:	>	
 * REDIR_HEREDOC : <<
 * REDIR_APPEND :	>>
 */

#ifndef MINITRY_ENUM_H

# define MINITRY_ENUM_H

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

enum e_error {
	OK,
	OPEN_FILE,
	FILE_NO_EXIST,
	FILE_NO_PERM,
	CMD_NOT_FOUND,
	FORK,
	MALLOC,
	PIPE_ERROR,
};

enum {
	LAST_PIPE_CLOSED = -2,
	NO_REDIR = -1,
	READ_FROM = 0,
	WRITE_TO = 1
};

# define HEREDOC_FILE "/Users/csteylae/goinfre/minishell_heredoc"

#endif

#endif