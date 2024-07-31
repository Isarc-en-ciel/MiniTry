/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:00:34 by csteylae          #+#    #+#             */
/*   Updated: 2024/07/31 12:02:36 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_H

# define MINITRY_H

#include "minitry_libraries.h"
#include "minitry_function.h"

/**
 * An enum to identify the different type of operator, including  redirection that can affect a command
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
}	t_tokens;

/**
 * !!!!Still on construction !!!!!!!
 *
 * A structure containing all the potential necessary informations about a redirction
 *
 * int fildes :	the optionnal file descriptor that can be associated to a redirection (such as "fd< filename")
 * char *filename : the name of the file in which the command is redirected to read from or to write to
 * type	: the kind of redirection
 *
 *  This struct and all its members are optional 
 */
typedef struct s_redirect 
{
	int					fildes;
	char				*filename;
	enum e_tokens		type;
	char				*heredoc_delimiter; //in case of heredoc. is set to null if type is not heredoc 
	
}   t_redirect;

/**
 * !!!!still in construction !!!
 *
 * A structure containing the commands that will by passed to the executor in form of an array of t_command
 *
 * - command->cmd		contains in cmd[0] command name and the rest of the array contains its potential options
 * - command->redirect	contains all the potential redirections that affect the command. It is an array of redirection. It is an optional member (can be set to NULL) (?)
 */
typedef struct s_command
{
    char        **cmd; // considerer les variable d'environnement seulement comme des options ?
    t_redirect  *redirect;
}   t_command;

/**
 *	A big structure that will contains all important information to parse from parsing to execution. 
 *
 *	data->envp	contains the envp variable
 *	data->tab	contains the array of commands parsed from readline()
 */
typedef struct s_data
{
    char         **env;
    t_command    *tab;
}   t_data;

# endif
