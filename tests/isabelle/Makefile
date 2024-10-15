NAME= minitry
CC=cc
CFLAGS= -Wall -Wextra -Werror
DFLAGS= -g -O0 -fsanitize=address

LIBFT = ../../lib/Libft/libft.a
PRINTF_LIB = ../../lib/ft_printf/libftprintf.a

SRCS= main.c \
	  ../../src/parsing/create_tokens.c \
	  ../../src/parsing/create_tokens2.c \
	  ../../src/parsing/retrieve_cmd.c \
	  ../../src/parsing/darray_utils.c \
	  ../../src/parsing/actual_parsing.c \
	  token_tester.c \

HEADER = ../../inc/*.h

OBJS=$(SRCS:.c=.o)

$(NAME) :$(OBJS)
	make bonus -C ../../lib/Libft
	make -C ../../lib/ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF_LIB) -lreadline -o $(NAME)

all : $(NAME)

clean :
	make clean -C ../../lib/Libft
	make clean -C ../../lib/ft_printf
	rm -rf $(OBJS)

fclean : clean
	make fclean -C ../../lib/Libft
	make fclean -C ../../lib/ft_printf
	rm -rf  $(NAME)
	rm -rf *.dSYM

re: fclean all

debug: CFLAGS += $(DFLAGS)
debug: re

.PHONY: all clean fclean re
