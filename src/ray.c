#include "cub3d.h"

static double	absd(double n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	init_steps(t_game *game, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_x = (game->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_y = (game->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_y;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->cam = 2 * x / (double)game->frame.width - 1;
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->cam;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->cam;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	if (ray->dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = absd(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = absd(1 / ray->dir_y);
	init_steps(game, ray);
}

void	perform_dda(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			break ;
	}
}

void	finish_ray(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		ray->wall = (ray->map_x - game->player.x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall = (ray->map_y - game->player.y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->line_h = (int)(game->frame.height / ray->wall);
	ray->draw_s = -ray->line_h / 2 + game->frame.height / 2;
	if (ray->draw_s < 0)
		ray->draw_s = 0;
	ray->draw_e = ray->line_h / 2 + game->frame.height / 2;
	if (ray->draw_e >= game->frame.height)
		ray->draw_e = game->frame.height - 1;
	if (ray->side == 0)
		wall_x = game->player.y + ray->wall * ray->dir_y;
	else
		wall_x = game->player.x + ray->wall * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->wall_x = wall_x;
}
