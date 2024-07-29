NAME	= libft.a
SRC_DIR	= ./srcs/
SRCS	= ft_isdigit.c ft_memset.c ft_striteri.c ft_strrchr.c\
		ft_isprint.c ft_putchar_fd.c ft_strjoin.c ft_strtrim.c\
		ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcat.c ft_substr.c\
		ft_bzero.c ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c\
		ft_calloc.c  ft_memchr.c ft_putstr_fd.c ft_strlen.c ft_toupper.c\
		ft_isalnum.c ft_memcmp.c ft_split.c ft_strmapi.c\
		ft_isalpha.c ft_memcpy.c ft_strchr.c ft_strncmp.c\
		ft_isascii.c  ft_memmove.c ft_strdup.c ft_strnstr.c\
		ft_printf.c ft_putstr.c ft_putnbr.c ft_putp.c get_next_line_safe.c\
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_strcmp.c\
		ft_lstadd_back.c ft_lstsize.c ft_lstadd_front.c\
		ft_lstclear.c ft_lstdelone.c ft_lstiter.c
SRCS	:= $(addprefix $(SRC_DIR), $(SRCS))
OBJS	= $(SRCS:.c=.o)
CC		= cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I. -c $< -o $@

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS) $(OBJS_B)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
