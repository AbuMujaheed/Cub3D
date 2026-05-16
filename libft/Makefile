NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isdigit.c ft_memset.c \
	ft_putchar_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
