/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:20:42 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/15 14:22:58 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_STRUCT_H

# define MINITRY_STRUCT_H

#include "minitry.h"
#include "minitry_enum.h"

typedef struct s_lexer
{
    char			*word;
    int				is_there_a_space;
	enum e_tokens	type;
}   t_lexer;

typedef	struct	s_stock
{
	int	nbr_elem;
	t_lexer	*cmd;
}	t_stock;

/**
 * A structure containing all the potential necessary informations about a redirction
 *
 * int fd (optionnal):	The file descriptor that can be associated to a redirection (such as "fd< filename")
 * char *filename :	The name of the file that redirects the input or output stream to read from or write to.
 * heredoc_delimiter (optionnal) :	Only for the case of REDIR_HEREDOC (noted "<< name_of_delimiter"). In all other case of redirection it will be set to NULL.
 * e_tokens typ	: The type of the redirection (<, >, <<, >>)
 *
 *  This struct and all its members are optional 
 */
typedef struct s_redirect 
{
	int					fd;
	char				*filename;
	char				*hd_delimiter;
	enum e_tokens		type;
}   t_redirect;

/**
	An array of structure redirection.
	int	size : the number of redirection that affect the command
*/
typedef struct	s_redir_array
{
	t_redirect	*array;
	int			size;
}	t_redir_array;

typedef struct	error
{
	char 			*str_perror;
	enum e_error	code;
}	t_error;
/**
 * A structure containing the commands that will be passed to the execution
 * in form of an array of t_command
 *
 * command->cmd	: an array of strings, as char **argv. Contains in cmd[0] the command name and the others indexes contains its potential options
 * command->redirection	: an array that kept in the order in which they appear in input, from left to righ,	all redirections that can affects a cmd	
 */
typedef struct s_command
{
	char			**cmd;
	t_redir_array	redirection;
	int				fd_in; //exec
	int				fd_out; //exec
	t_error			error;
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
