#include "cub3d.h"

static void	choose_texture(t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x < 0)
		ray->tex = TEX_W;
	else if (ray->side == 0 && ray->dir_x >= 0)
		ray->tex = TEX_E;
	else if (ray->side == 1 && ray->dir_y < 0)
		ray->tex = TEX_N;
	else
		ray->tex = TEX_S;
}

static int	texture_x(t_game *game, t_ray *ray)
{
	int	x;

	x = ray->tex_x;
	if (ray->tex == TEX_W || ray->tex == TEX_S)
		x = game->tex[ray->tex].width - x - 1;
	if (x < 0)
		x = 0;
	if (x >= game->tex[ray->tex].width)
		x = game->tex[ray->tex].width - 1;
	return (x);
}

void	draw_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	step;
	double	pos;
	int		y;
	int		tex_y;

	choose_texture(ray);
	tex = &game->tex[ray->tex];
	step = 1.0 * tex->height / ray->line_h;
	pos = (ray->draw_s - WIN_H / 2 + ray->line_h / 2) * step;
	y = ray->draw_s;
	while (y <= ray->draw_e)
	{
		tex_y = (int)pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel(&game->frame, x, y,
			get_pixel(tex, texture_x(game, ray), tex_y));
		pos += step;
		y++;
	}
}
