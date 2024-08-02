NAME	= minishell
SRC_DIR = srcs/
SRCS	= builtins/cd.c builtins/echo.c builtins/env.c builtins/pwd.c builtins/export.c builtins/unset.c\
		main.c exit.c parse.c utils.c exec.c environment.c init.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a
CC		= cc -Wall -Wextra -Werror -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) $(LIB) -o $(NAME) -lreadline -fsanitize=address

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
