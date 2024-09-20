/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:20:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/09/20 11:51:38 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_STRUCT_H

# define MINITRY_STRUCT_H

#include "minitry_lib.h"

/**
 * An enum to identify the different type of redirection that can affect a command
 *
 * REDIR_IN :	<
 * REDIR_OUT:	>	
 * REDIR_HEREDOC : <<
 * REDIR_APPEND :	>>
 */
enum e_tokens {
    PIPE,
    QUOTE,
    D_QUOTE,
    WORD,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APP,
    REDIR_HEREDOC
};

typedef struct s_lexer
{
    char    *word;
    int     is_there_a_space;
	enum e_tokens	type;
}   t_lexer;

/**
 * A structure containing all the potential necessary informations about a redirction
 *
 * int fd (optionnal):				The file descriptor that can be associated to a redirection (such as "fd< filename")
 * char *filename :					The name of the file that redirects the input or output stream to read from or write to.
 * heredoc_delimiter (optionnal) :	Only for the case of REDIR_HEREDOC (noted "<< name_of_delimiter"). In all other case of redirection it will be set to NULL.
 *
 *  This struct and all its members are optional 
 */

typedef struct s_redirect 
{
	int					fd;
	char				*filename;
	char				*hd_delimiter;
}   t_redirect;

/**
	t_redirect array : the array of struct. Its size is computated from the parsing step.
/ An array of structure redirection.
	int	size : the number of redirection of the same type that affect the command
/
*/
typedef struct	s_redir_array
{
	t_redirect	*array;
	int			size;
}	t_redir_array;

/**
 * A structure containing the commands that will be passed to the execution
 * in form of an array of t_command
 *
 * - command->cmd	: 				an array of strings, as char **argv. Contains in cmd[0] the command name and the others indexes contains its potential options
 * - command->in (optionnal)	: 	an array of struct t_redirect. Contains all the possible IN_REDIR (noted <) that can affect a command
 * - command->out (optionnal)	:	an array of struct t_redirect. Contains all the possible OUT_REDIR (noted >) that can affect a cmd
 * - command->heredoc (optionnal) : an array of struct t_redirect. Contains all the possible HEREDOC_REDIR (noted << delimitor_name). In that case, the redirect->heredoc_delimiter is not NULL and indicate the name of the delimiter.
 * - command->append (optionnal) :	an array of struct t_redirect. Contains all the possible APPEND_REDIR (noted >>).
 */
typedef struct s_command
{
	char			**cmd;
	t_redir_array	*in;
	t_redir_array	*out;
	t_redir_array	*append;
	t_redir_array	*heredoc;
}	t_command;

/**
 *	A big structure that will contains all important information
 *
 *	shell.envp	contains the envp variable
 *	shell.tab	contains the array of commands parsed from readline()
 *	shell.tab_size 	the size of the array. Is the nb of commands passed
 *	shell.error	an int to indicate if an error occurs, 
 *		idk if we will keep it (just use in init_shell() in src/parsing/minitry.c
 */
typedef struct s_shell
{
	char		**env;
	t_command	*tab;
	int			tab_size;
	int			error;
	int			exit_status;
}	t_shell;

typedef struct s_darray
{
	t_lexer	*content;
	size_t	max_size;
	size_t	actual_size;
	size_t	block;
}	t_darray;

#endif
