/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitry_function.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csteylae <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:24:03 by csteylae          #+#    #+#             */
/*   Updated: 2024/10/24 15:25:52 by csteylae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITRY_FUNCTION_H

# define MINITRY_FUNCTION_H

#include "minitry_struct.h"
#include "minitry_lib.h"
#include "minitry_enum.h"

/*file src/environment/init_env.c */
char	**init_env(char **envp);

/*file src/environment/test_env.c */
void	ft_print_cmd(t_shell *shell);
void	test_env(t_shell *shell, char *input); //function added to your minitry.c to avoid the pollution of that file 


/* repo init */
t_shell	init_shell(void);

/* repo builtins */
int	ft_cd(char **args);
void	exec_env(t_shell *shell);

/* repo execution */
void	exec_command(t_shell *shell, int nb); /*file exec_command.c */
int		exec_prompt(t_shell *shell); /* file exec_prompt.c */
void	delete_heredoc_file(t_command *cmd);/* file exec_prompt.c */
void	exec_pipeline(t_shell *shell); //file src/execution/exec_pipeline.c
void	perform_redirection(t_shell *shell, t_command *cmd); //file redirection.c
void	redirect_io(t_shell *shell, int fd_in, int fd_out); //file redirection.c
t_command	*pseudo_parsing(t_shell *shell, char *input);
void	create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redirection);

/* repo utils */
//file free_struct.c :
void	free_tab_char(char **tab);
void	free_redir_array(t_redir_array redirection);
void	free_cmd(t_command *cmd);
void	free_tab_cmd(int size, t_command *tab);
void	free_shell(t_shell *shell);

//file set_error.c
t_error	set_error(char *str, enum e_error code);

//file exit_error.c
void	exit_error(t_shell *shell, char *error);

//tokenisation
t_lexer	create_pipe(char *input, int *position, t_lexer token);
t_lexer	create_redirect_in(char *input, int *position, t_lexer token);
t_lexer	create_redirect_out(char *input, int *position, t_lexer token);
t_lexer	create_doubleq(char *input, int *position, t_lexer token);
t_lexer	create_simpleq(char *input, int *position, t_lexer token);
t_lexer	create_word(char *input, int *position, t_lexer token);
int	    check_open_quotes(char *str, char c, int j);
void	*ft_memcpy_plus(void *dst, const void *src, int start, int n);

//dynamic array
t_darray	*retrieve_cmd(char *input);
int	    init_array(t_darray *darray, size_t block_size);
int	reserve_array(t_darray *darray);
void	free_temp_array(t_darray *darray);
t_darray	realloc_array(t_darray *darray);
int 	error_fct(t_darray *tab);
int	    ft_isspace(char c);
int     is_delimiter(char c);
int     print_token_tab(t_darray *cmd);
void	ft_print_redir_type(enum e_tokens token);

//parsing
int	parsing_starter(t_darray *tokens);
int	count_pipes(t_darray *tokens);
int	into_cmds(int i, t_darray *tokens, t_stock *tab);
int	fill_cmb_tab(int *j, int *l, t_darray *tokens, t_stock *tab);
int	nbr_elem_cmd(int i, t_darray *tokens, t_stock *tab);

#endif
