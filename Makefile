# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iwaslet <iwaslet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/19 12:04:57 by csteylae          #+#    #+#              #
#    Updated: 2025/02/24 17:05:33 by csteylae         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
CC=cc
CFLAGS= -Wall -Wextra -Werror -g -O0 #-fsanitize=address -gdwarf-4 
DFLAGS= -g -O0 -fsanitize=address

LIBFT = lib/Libft/libft.a
PRINTF_LIB = lib/ft_printf/libftprintf.a

SRCS= lib/get_next_line/get_next_line.c \
	  lib/get_next_line/get_next_line_utils.c \
	  src/parsing/main.c \
	  src/init/init_shell.c \
	  src/expander/var_expansion.c \
	  src/expander/expand_exit_status.c \
	  src/expander/expand_env_var.c \
	  src/expander/update_expanded_value.c \
	  src/builtins/builtin_utils.c \
	  src/builtins/ft_cd.c \
	  src/builtins/ft_env.c \
	  src/builtins/ft_pwd.c \
	  src/builtins/ft_echo.c \
	  src/builtins/ft_exit.c \
	  src/builtins/ft_unset.c \
	  src/builtins/ft_export.c \
	  src/builtins/export_without_arg.c \
	  src/parsing/create_tokens.c \
	  src/parsing/create_tokens2.c \
	  src/parsing/darray_utils.c \
	  src/parsing/retrieve_cmd.c \
	  src/parsing/retrieve_utils.c \
	  src/parsing/retrieve_utils2.c \
	  src/parsing/token_tester.c \
	  src/parsing/parsing_starter.c \
	  src/parsing/actual_parsing.c \
	  src/parsing/error_fcts.c \
	  src/parsing/expander.c \
	  src/parsing/tab_cleaner.c \
	  src/environment/init_env.c \
	  src/environment/function_env.c \
	  src/environment/array_to_list.c \
	  src/environment/list_to_array.c \
	  src/environment/update_env.c \
	  src/environment/get_env_value.c \
	  src/environment/update_underscore_var.c \
	  src/environment/compare_key.c \
	  src/environment/increment_shlvl.c \
	  src/environment/get_previous_env_var.c \
	  src/environment/ft_get_env.c \
	  src/execution/exec_command.c \
	  src/execution/exec_prompt.c \
	  src/execution/exec_pipeline.c \
	  src/execution/redirection.c \
	  src/execution/heredoc.c \
	  src/execution/get_exit_status.c \
	  src/execution/init_pipeline.c \
	  src/execution/control_io_pipeline.c \
	  src/execution/close_fd.c \
	  src/execution/find_executable_path.c \
	  src/execution/exec_builtins.c \
	  src/utils/free_struct.c \
	  src/utils/exit_error.c \
	  src/utils/set_error.c \
	  src/signal/setup_signal.c \
	  src/signal/handle_sigint.c \
	  src/parsing/from_stock_to_exec_cmd.c \
	  src/parsing/from_stock_to_redirection.c \
	  src/parsing/get_cmd_args.c \

HEADER = ../../inc/*.h

OBJS=$(SRCS:.c=.o)

$(NAME) :$(OBJS)
	make bonus -C lib/Libft
	make -C lib/ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF_LIB) -lreadline -o $(NAME)

all : $(NAME)

clean :
	make clean -C lib/Libft
	make clean -C lib/ft_printf
	rm -rf $(OBJS)

fclean : clean
	make fclean -C lib/Libft
	make fclean -C lib/ft_printf
	rm -rf  $(NAME)
	rm -rf *.dSYM

re: fclean all

debug: CFLAGS += $(DFLAGS)
debug: re
valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supp.supp ./minishell

.PHONY: all clean fclean re
