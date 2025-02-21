/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_function.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:38:18 by iwaslet           #+#    #+#             */
/*   Updated: 2025/02/21 12:54:19 by iwaslet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTION_H

# define MINISHELL_FUNCTION_H

# include "minishell_struct.h"
# include "minishell_lib.h"
# include "minishell_enum.h"

/* repo signal */
struct sigaction	init_sigaction(void(*fct)(int));
void				setup_signal(t_shell *sh, void(*fct)(int));
void				handle_sigint_interactive_mode(int signum);
void				handle_sigint_child_process(int signum);
struct sigaction	setup_signal_in_children(void);
struct sigaction	setup_signal_in_parent(void);

/*repo environment */
char				**init_env(char **envp);
t_env_list			*new_env_list(char *key, char *value, bool is_init);
void				lst_addback(t_env_list **head, t_env_list *new);
void				delete_env(t_env_list *elem);
int					get_list_size(t_env_list *head);
void				destroy_lst(t_env_list **head);
t_env_list			*array_to_list(char **env);
char				**list_to_array(t_env_list **head);
void				ft_print_list(t_env_list *head);
t_env_list			*get_env(char *key, t_env_list **head);
char				*get_env_value(t_env_list *head, char *key);
t_env_list			*get_prev_env(t_env_list **head, char *key);
bool				update_env(t_env_list **head, char *key, char *value);
void				update_underscore_var(t_shell *shell);
bool				key_found(char *s1, char *s2);
void				incr_shlvl(t_shell *sh);

/* repo expander */
int					expand_var(t_shell *shell, char **word);
char				*update_expanded_value(char *ret, char *word, int count);
int					expand_exit_status(char **retp, int exit_status);
int					expand_env_var(char **retp, char *word, int i, char **env);
bool				is_the_exit_status(char *word, int i);
bool				is_an_env_var(char *word, int i);

/* repo init */
t_shell				init_shell(char **envp);

/* repo builtins */
bool				init_env_list(t_env_list **head,
						t_command *cmd, char **env);
int					builtin_error(t_command *cmd, char *str,
						enum e_error code, t_env_list **head);
void				build_envp(t_env_list **head, t_command *cmd, char ***envp);
bool				is_key_format(t_command *cmd, char *str);
int					ft_cd(t_shell *sh, t_command *cmd);
int					ft_env(t_shell *sh, t_command *cmd);
int					ft_pwd(t_shell *sh, t_command *cmd);
int					ft_echo(t_shell *sh, t_command *cmd);
int					ft_exit(t_shell *sh, t_command *cmd);
int					ft_unset(t_shell *sh, t_command *cmd);
int					ft_export(t_shell *sh, t_command *cmd);
void				export_without_arg(t_env_list **head, t_command *cmd);

/* repo execution */
void				init_pipeline(t_shell *sh, int i,
						int pipe_fd[2], int prev_fd);
void				init_child_pid(t_shell *sh);
t_builtin			*find_builtin(t_shell *sh, t_command *cmd);
void				perform_redirection(t_shell *shell, t_command *cmd);
void				create_heredoc(t_shell *shell,
						t_command *cmd, t_redirect *redirection);
void				delete_heredoc_file(t_command *cmd);
void				redirect_io(t_shell *shell, int fd_in, int fd_out);
void				exec_prompt(t_shell *shell);
void				exec_external_cmd(t_shell *shell, int nb);
void				exec_pipeline(t_shell *shell);
t_command			*pseudo_parsing(t_shell *shell, char *input);
int					get_exit_status(t_command *cmd, pid_t pid);
int					wait_children(t_shell *shell,
						pid_t *child_pid, int child_nb);
int					configure_pipeline(t_shell *sh,
						int i, int pipe_fd[2], int prev_fd);
int					close_fd(int *p_fd);
void				close_all_fds(int pipe_fd[2],
						int *prev_fd, int *in, int *out);
char				*find_executable_path(t_shell *sh, int n, t_command *cmd);
void				exit_child(t_shell *sh, int pipe_fd[2], int prev_fd, int i);
void				exec_builtin(t_builtin *builtin,
						t_command *cmd, t_shell *sh);
void				terminate_pipeline(t_shell *sh, int i, int prev_fd);
t_shell				*clean_prompt(t_shell *sh);

/* repo utils */
void				free_tab_char(char **tab);
void				free_redir_array(t_redir_array redirection);
void				free_cmd(t_command *cmd);
void				free_tab_cmd(int size, t_command *tab);
void				free_shell(t_shell *shell);
//file set_error.c
t_error				set_error(char *str, enum e_error code);
//file exit_error.c
void				exit_error(t_shell *shell, char *error);

//tokenisation
t_lexer				create_pipe(char *input, int *position, t_lexer token);
t_lexer				create_redirect_in(char *input,
						int *position, t_lexer token);
t_lexer				create_redirect_out(char *input,
						int *position, t_lexer token);
t_lexer				create_doubleq(char *input, int *position, t_lexer token);
t_lexer				create_simpleq(char *input, int *position, t_lexer token);
t_lexer				create_word(char *input, int *position, t_lexer token);
int					check_open_quotes(char *str, char c, int j);
void				*ft_memcpy_plus(void *dst,
						const void *src, int start, int n);

//dynamic array
t_darray			*retrieve_cmd(char *input, t_shell *shell);
int					retrieve_loop(char *input, t_darray *tab, int i, int j);
int					init_array(t_darray *darray, size_t block_size);
int					reserve_array(t_darray *darray);
void				free_temp_array(t_darray *darray);
void				free_final_array(t_darray *darray);
t_darray			realloc_array(t_darray *darray);
int					error_fct(t_darray *tab, int i);
int					ft_isspace(char c);
int					is_delimiter(char c);
int					print_token_tab(t_darray *cmd);
void				ft_print_redir_type(enum e_tokens token);
int					retrieve_pipe(char *input, int *i, int *j, t_darray *tab);
int					retrieve_in(char *input, int *i, int *j, t_darray *tab);
int					retrieve_out(char *input, int *i, int *j, t_darray *tab);
int					retrieve_dquotes(char *input, int *i,
						int *j, t_darray *tab);
int					retrieve_squotes(char *input, int *i,
						int *j, t_darray *tab);
int					retrieve_word(char *input, int *i, int *j, t_darray *tab);

//parsing
t_command			*parsing(char *input, t_shell *shell);
t_stock				*parsing_starter(t_darray *tokens,
						t_stock	*tab, t_shell *shell);
int					count_pipes(t_darray *tokens);
t_stock				*error_return(t_darray *tokens, int i, t_shell *shell);
int					into_cmds(int i, t_darray *tokens, t_stock *tab);
int					fill_cmb_tab(int *j, int *l,
						t_darray *tokens, t_stock *tab);
int					nbr_elem_cmd(int i, t_darray *tokens, t_stock *tab);
int					check_grammar(t_stock *tab, int cmds);
int					is_redirect(enum e_tokens token);
int					is_word_token(enum e_tokens token);
void				free_first_degree_tab(t_stock *tab, int i);
void				free_second_degree_tab(t_stock *tab, int i);
t_command			*error_parsing(t_stock *tab, int i, t_shell *shell);

//expander
t_stock				*expander(t_stock *tab, t_shell *shell);
int					expand_cmd(t_lexer *cmd, t_shell *shell, int size);
int					join_cmd(t_lexer *cmd, int size, int i, int a);
int					ft_strcmp(const char *s, char n);
char				*ft_strcpy(const char *s1, char *s2);
t_stock				*tab_cleaner(t_stock *tab);
int					clean_cmd(t_lexer *cmd, t_lexer **new_cmd,
						int nbr_elem, int *new_nbr_elem);
int					count_new_elem(t_lexer *cmd,
						int nbr_elem, int *new_nbr_elem);
int					copy_token(t_lexer cmd, t_lexer *new_cmd);
void				new_empty_cmd(t_lexer *new_cmd);
int					make_new_cmd(t_lexer *cmd, t_lexer **new_cmd, int nbr_elem);

//testing parsing
int					print_token_tab(t_darray *cmd);
void				ft_print_redir_type(enum e_tokens token);
int					print_stock_tab(t_stock *tab, int cmds);

//src/parsing/from_stock_to_cmd
t_command			*from_stock_to_cmd(t_stock *stock, t_shell *sh);

//from_stock_to_redirection
bool				is_redir_operator(enum e_tokens type);
t_redir_array		get_redirections(t_lexer *cmd, int cmd_size, int *pstatus);

#endif
