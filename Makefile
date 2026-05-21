NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -std=gnu17
INC = -Iincludes -Ilibft -I$(MLX_DIR)
MLX_DIR = mlx/minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = libft/libft.a

SRCS = src/main.c src/error.c src/free.c src/file.c src/parse.c \
	src/config.c src/color.c src/map.c src/player.c src/mlx.c \
	src/hooks.c src/move.c src/render.c src/ray.c src/draw.c \
	src/utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX_DIR)/libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
