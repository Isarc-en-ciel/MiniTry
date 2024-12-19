/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enum.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:33:56 by iwaslet           #+#    #+#             */
/*   Updated: 2024/12/19 18:44:07 by csteylae         ###   ########.fr       */
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
	SUCCESS = 0,
	OK = 0,
	BUILTIN_OPT = 1,
	BAD_ARG, 
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

# define NB_OF_BUILTIN 7
# define CHILD_PROCESS 0
# define SUCCESS 0
# define FAIL 1
# define HEREDOC_FILE "/tmp/minishell_heredoc"
# define SHELL_INVOK "_=./minishell"
# define NOENT_PERROR "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory"
#endif
