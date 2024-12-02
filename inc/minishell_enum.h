/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enum.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:56 by iwaslet           #+#    #+#             */
/*   Updated: 2024/12/02 15:34:41 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * An enum to identify the different type
 * of redirection that can affect a command
 * REDIR_IN :	<
 * REDIR_OUT:	>	
 * REDIR_HEREDOC : <<
 * REDIR_APPEND :	>>
 */

#ifndef MINISHELL_ENUM_H

# define MINISHELL_ENUM_H

enum e_tokens
{
	PIPE = 1,
	QUOTE,
	D_QUOTE,
	WORD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	REDIR_HEREDOC,
};

enum e_error
{
	OK = 0,
	BUILTIN_OPT = 2,
	OPEN_FILE,
	FILE_NO_EXIST = 127,
	FILE_NO_PERM,
	CMD_NOT_FOUND = 127,
	FORK,
	MALLOC,
	SYSCALL_ERROR = 1,
	PIPE_ERROR,
	CD_ERROR,
};

enum
{
	LAST_PIPE_CLOSED = -2,
	NO_REDIR = -1,
	READ_FROM = 0,
	WRITE_TO = 1
};

# define SUCCESS 0
# define FAIL 1
# define HEREDOC_FILE "/Users/csteylae/goinfre/minishell_heredoc"

#endif
