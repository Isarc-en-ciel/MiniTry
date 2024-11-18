/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:18 by iwaslet           #+#    #+#             */
/*   Updated: 2024/11/18 16:18:56 by csteylae         ###   ########.fr       */
/*   Updated: 2024/11/18 15:54:13 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H

# define MINISHELL_FUNCTION_H

# include "minishell_struct.h"
# include "minishell_lib.h"
# include "minishell_enum.h"

/*repo environment */
char		**init_env(char **envp); //env_list.c
t_env_list	*new_env_list(char *key, char *value); //env_list_func.c
void		lst_addback(t_env_list **head, t_env_list *new); //env_list_func.c
void		delete_env(t_env_list *elem);
t_env_list	*get_env(char *key, t_env_list *head);
t_env_list	*env_modify_value(char *key, char *new_value, t_env_list **head);
int			get_list_size(t_env_list *head); //env_list_func.c
void		destroy_lst(t_env_list **head); //env_list_func.c
t_env_list	*array_to_list(char **env);
char		**list_to_array(t_env_list **head);
void		ft_print_list(t_env_list *head);

/*repo builtins*/
t_env_list	*init_list(char **env, t_command *cmd);

/*file src/environment/test_env.c */
void		ft_print_cmd(t_shell *shell);
void		test_env(t_shell *shell, char *input); //function added to your minitry.c to avoid the pollution of that file 

/* repo init */
t_shell		init_shell(void);

/* repo builtins */
int			ft_cd(char ***env, t_command *cmd);
int			ft_env(char ***env, t_command *cmd);
int			ft_pwd(char ***env, t_command *cmd);
int			ft_echo(char ***env, t_command *cmd);

/* repo execution */
void		exec_command(t_shell *shell, int nb); /*file exec_command.c */
int			exec_prompt(t_shell *shell); /* file exec_prompt.c */
void		delete_heredoc_file(t_command *cmd);/* file exec_prompt.c */
void		exec_pipeline(t_shell *shell); //file src/execution/exec_pipeline.c
void		perform_redirection(t_shell *shell, t_command *cmd); //file redirection.c
void		redirect_io(t_shell *shell, int fd_in, int fd_out); //file redirection.c
t_command	*pseudo_parsing(t_shell *shell, char *input);
void		create_heredoc(t_shell *shell, t_command *cmd, t_redirect *redirection);

/* repo utils */
void		free_tab_char(char **tab);
void		free_redir_array(t_redir_array redirection);
void		free_cmd(t_command *cmd);
void		free_tab_cmd(int size, t_command *tab);
void		free_shell(t_shell *shell);
//file set_error.c
t_error		set_error(char *str, enum e_error code);
//file exit_error.c
void		exit_error(t_shell *shell, char *error);

//tokenisation
t_lexer		create_pipe(char *input, int *position, t_lexer token);
t_lexer		create_redirect_in(char *input, int *position, t_lexer token);
t_lexer		create_redirect_out(char *input, int *position, t_lexer token);
t_lexer		create_doubleq(char *input, int *position, t_lexer token);
t_lexer		create_simpleq(char *input, int *position, t_lexer token);
t_lexer		create_word(char *input, int *position, t_lexer token);
int			check_open_quotes(char *str, char c, int j);
void		*ft_memcpy_plus(void *dst, const void *src, int start, int n);

//dynamic array
t_darray	*retrieve_cmd(char *input);
int			retrieve_loop(char *input, t_darray *tab, int i, int j);
int			init_array(t_darray *darray, size_t block_size);
int			reserve_array(t_darray *darray);
void		free_temp_array(t_darray *darray);
void		free_final_array(t_darray *darray);
t_darray	realloc_array(t_darray *darray);
int			error_fct(t_darray *tab);
int			ft_isspace(char c);
int			is_delimiter(char c);
int			print_token_tab(t_darray *cmd);
void		ft_print_redir_type(enum e_tokens token);
int			retrieve_pipe(char *input, int *i, int *j, t_darray *tab);
int			retrieve_in(char *input, int *i, int *j, t_darray *tab);
int			retrieve_out(char *input, int *i, int *j, t_darray *tab);
int			retrieve_dquotes(char *input, int *i, int *j, t_darray *tab);
int			retrieve_squotes(char *input, int *i, int *j, t_darray *tab);
int			retrieve_word(char *input, int *i, int *j, t_darray *tab);

//parsing
int			parsing_starter(t_darray *tokens);
int			count_pipes(t_darray *tokens);
int			into_cmds(int i, t_darray *tokens, t_stock *tab);
int			fill_cmb_tab(int *j, int *l, t_darray *tokens, t_stock *tab);
int			nbr_elem_cmd(int i, t_darray *tokens, t_stock *tab);
int	        check_grammar(t_stock *tab, int cmds);

//testing parsing
int			print_token_tab(t_darray *cmd);
void		ft_print_redir_type(enum e_tokens token);
int			print_stock_tab(t_stock *tab, int cmds);

#endif
