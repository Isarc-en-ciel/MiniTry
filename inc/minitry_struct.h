/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:39:29 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/30 12:04:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINITRY_STRUCT_H

# define MINITRY_STRUCT_H

#include "minitry_enum.h"
#include "minitry_lib.h"

typedef struct s_lexer
{
    char			*word;
    int				is_there_a_space;
	enum e_tokens	type;
}   t_lexer;

typedef struct s_darray
{
	t_lexer	*content;
	size_t	max_size;
	size_t	actual_size;
	size_t	block;
}	t_darray;

typedef	struct	s_stock
{
	int	nbr_elem;
	t_lexer	*cmd;
}	t_stock;

/**
 * A struct containing all the potential necessary informations about redirction
 *
 * int fd (optionnal): file descriptor associated to a redirection, 
 * such as "fd< filename")
 *
 * char *filename :	name of the file that redirects the input or output stream
 *
 * heredoc_delimiter (optionnal) :	Only for REDIR_HEREDOC. 
 * if its  not a heredoc, set to NULL.
 *
 * e_tokens typ	: The type of the redirection (<, >, <<, >>)
 */
typedef struct s_redirect
{
	int					fd; //idk if we keep it 
	char				*filename; //malloc
	char				*hd_delimiter; //malloc
	enum e_tokens		type;
}   t_redirect;

/**
 * 	A struct that contains the array of redirection and the size of that array
 *
 * int	size : the number of redirection that affect the command. 0 if no redir
 *
 * t_redirect *array : the malloced array that contains all redirections,
 * it keeps the redir in their order, form left to right,is NULL if no redir
*/
typedef struct	s_redir_array
{
	t_redirect	*array; //malloc, array = malloc(sizeof(*array) * size)
	int			size;
}	t_redir_array;

typedef struct	error
{
	char 			*str_perror;
	enum e_error	code;
}	t_error;

/**
 * Struct containing the command that will be passed to the execution
 *
 * command->cmd	: an array of strings. Contains the command name at index 0,
 * and its potential options
 *
 * command->redirection	: the t_redir array that kept in their order all redir
 *  that can affects a cmd	
 */
typedef struct s_command
{
	char			**cmd;
	t_redir_array	redirection;
	int				fd_in; //exec
	int				fd_out; //exec
	t_error			error;
}	t_command;

/*
 *	A temp struct used inside builtins functions to manage the environment 
 *	easely. Before the return of the builtin function, once all modifications
 *	are done,  this struct will be copied into an array of str (char **env)
 *	and then destroyed; 
 */
typedef struct	s_env_list
{
	char		*key;
	char		*value;
	struct s_env_list	*next;
}	t_env_list;

typedef int (*builtin_func) (char ***env, t_command *cmd);

typedef struct s_builtin
{
	const char		*name;
	builtin_func	func;
}	t_builtin;

/**
 *	Our master struc that will contain all we need to run minishell
 *
 *	shell.envp	contains the envp variable
 *	shell.tab	contains the array of commands
 *	shell.tab_size 	the size of the array. Is the nb of commands passed
 *	shell.exit_status: give the exit stqtus of the last command executed
 */
typedef struct s_shell
{
	char		**env;
	t_command	*tab;
	int			tab_size;
	int			exit_status;
	t_builtin	builtin_cmds[7];
}	t_shell;

#endif
