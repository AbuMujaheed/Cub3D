#include "cub3d.h"

int	die(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	game_error(t_game *game, char *msg)
{
	free_game(game);
	return (die(msg));
}
