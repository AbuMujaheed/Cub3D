#include "cub3d.h"

int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	if (key == KEY_W)
		game->keys.w = 1;
	if (key == KEY_A)
		game->keys.a = 1;
	if (key == KEY_S)
		game->keys.s = 1;
	if (key == KEY_D)
		game->keys.d = 1;
	if (key == KEY_LEFT)
		game->keys.left = 1;
	if (key == KEY_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->keys.w = 0;
	if (key == KEY_A)
		game->keys.a = 0;
	if (key == KEY_S)
		game->keys.s = 0;
	if (key == KEY_D)
		game->keys.d = 0;
	if (key == KEY_LEFT)
		game->keys.left = 0;
	if (key == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

int	loop_game(t_game *game)
{
	move_player(game);
	render(game);
	return (0);
}
