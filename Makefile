NAME	= minishell
SRC_DIR = srcs/
SRCS	= 	executor.c\
			utils2.c\
			exec.c\
			init.c\
			parser/rdir_utilts.c\
			parser/pipe_utilts.c\
			parser/parse.utils.c\
			parser/lexer.c\
			parser/expand_envs.c\
			parser/expand_env.c\
			parser/rdir_pipe.c\
			parser/free_error.c\
			parser/parse.c\
			parser/parser.c\
			builtins/exit.c\
			builtins/unset.c\
			builtins/env.c\
			builtins/pwd.c\
			builtins/export.c\
			builtins/cd.c\
			builtins/exec_builtin.c\
			builtins/echo.c\
			utils.c\
			main.c\
			environ.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
LIB		= ./libft/libft.a
CC		= cc -Wall -Wextra -Werror -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(OBJS) $(LIB) -o $(NAME) -lreadline

clean:
	rm -rf $(OBJS)
	make clean -C libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
