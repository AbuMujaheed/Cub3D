#include "cub3d.h"

void	set_player_dir(t_player *p, char c)
{
	p->dir_x = 0;
	p->dir_y = -1;
	p->plane_x = 0.66;
	p->plane_y = 0;
	if (c == 'S')
	{
		p->dir_y = 1;
		p->plane_x = -0.66;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player(game->map.grid[y][x]))
			{
				game->map.players++;
				game->player.x = x + 0.5;
				game->player.y = y + 0.5;
				set_player_dir(&game->player, game->map.grid[y][x]);
			}
			x++;
		}
		y++;
	}
	return (game->map.players == 1);
}
