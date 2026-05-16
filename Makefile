NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Iincludes -Ilibft
MLX_DIR = minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = libft/libft.a

SRCS = src/main.c src/error.c src/free.c src/file.c src/parse.c \
	src/config.c src/color.c src/map.c src/player.c src/mlx.c \
	src/hooks.c src/move.c src/render.c src/ray.c src/draw.c \
	src/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
