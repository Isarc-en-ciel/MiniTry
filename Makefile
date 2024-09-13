NAME= minitry
CC=cc
CFLAGS= -Wall -Wextra -Werror
DFLAGS= -g -O0 -fsanitize=address

LIBFT = lib/Libft/libft.a
PRINTF_LIB = lib/ft_printf/libftprintf.a

SRCS= src/parsing/minitry.c \
	  src/builtins/cd.c \
	  src/builtins/env.c \
	  src/environment/init_env.c\
	  src/environment/test_env.c \
	  src/execution/exec_command.c \
	  src/execution/exec_prompt.c \
	  src/execution/exec_pipeline.c \
	  src/utils/free_struct.c \
	  src/utils/exit_error.c \

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

.PHONY: all clean fclean re
