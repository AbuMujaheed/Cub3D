#include "cub3d.h"

static int	clear_cell(t_game *game, double x, double y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (0);
	return (game->map.grid[(int)y][(int)x] != '1'
		&& game->map.grid[(int)y][(int)x] != ' ');
}

static int	clear_position(t_game *game, double x, double y)
{
	return (clear_cell(game, x - PLAYER_RADIUS, y - PLAYER_RADIUS)
		&& clear_cell(game, x + PLAYER_RADIUS, y - PLAYER_RADIUS)
		&& clear_cell(game, x - PLAYER_RADIUS, y + PLAYER_RADIUS)
		&& clear_cell(game, x + PLAYER_RADIUS, y + PLAYER_RADIUS));
}

static void	try_move(t_game *game, double x, double y)
{
	if (clear_position(game, x, game->player.y))
		game->player.x = x;
	if (clear_position(game, game->player.x, y))
		game->player.y = y;
}

static void	rotate(t_player *p, double speed)
{
	double	old_dir;
	double	old_plane;

	old_dir = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = old_dir * sin(speed) + p->dir_y * cos(speed);
	old_plane = p->plane_x;
	p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
	p->plane_y = old_plane * sin(speed) + p->plane_y * cos(speed);
}

void	move_player(t_game *game)
{
	double	ms;
	double	rs;

	ms = 0.055;
	rs = 0.04;
	if (game->keys.w)
		try_move(game, game->player.x + game->player.dir_x * ms,
			game->player.y + game->player.dir_y * ms);
	if (game->keys.s)
		try_move(game, game->player.x - game->player.dir_x * ms,
			game->player.y - game->player.dir_y * ms);
	if (game->keys.a)
		try_move(game, game->player.x - game->player.plane_x * ms,
			game->player.y - game->player.plane_y * ms);
	if (game->keys.d)
		try_move(game, game->player.x + game->player.plane_x * ms,
			game->player.y + game->player.plane_y * ms);
	if (game->keys.left)
		rotate(&game->player, -rs);
	if (game->keys.right)
		rotate(&game->player, rs);
}
