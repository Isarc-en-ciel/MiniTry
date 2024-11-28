NAME= minishell
CC=cc
CFLAGS= -Wall -Wextra -Werror
DFLAGS= -g -O0 -fsanitize=address
VALGRIND_FLAGS= -g -O0

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
	  src/parsing/create_tokens.c \
	  src/parsing/create_tokens2.c \
	  src/parsing/darray_utils.c \
	  src/parsing/retrieve_cmd.c \
	  src/parsing/retrieve_utils.c \
	  src/parsing/retrieve_utils2.c \
	  src/parsing/token_tester.c \
	  src/parsing/parsing_starter.c \
	  src/parsing/actual_parsing.c \
	  src/parsing/init_struct_shell.c \
	  src/environment/init_env.c \
	  src/environment/function_env.c \
	  src/environment/array_to_list.c \
	  src/environment/list_to_array.c \
	  src/environment/update_env.c \
	  src/execution/pseudo_parsing.c \
	  src/execution/exec_command.c \
	  src/execution/exec_prompt.c \
	  src/execution/exec_pipeline.c \
	  src/execution/redirection.c \
	  src/execution/heredoc.c \
	  src/execution/get_exit_status.c \
	  src/utils/free_struct.c \
	  src/utils/exit_error.c \
	  src/utils/set_error.c \

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
valgrind: CFLAGS += $(VALGRIND_FLAGS)
valgrind: re

.PHONY: all clean fclean re
