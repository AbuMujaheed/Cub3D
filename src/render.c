#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	src = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}

static void	fill_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->frame.height)
	{
		x = 0;
		while (x < game->frame.width)
		{
			if (y < game->frame.height / 2)
				put_pixel(&game->frame, x, y, game->cfg.ceiling);
			else
				put_pixel(&game->frame, x, y, game->cfg.floor);
			x++;
		}
		y++;
	}
}

void	render(t_game *game)
{
	t_ray	ray;
	int		x;

	fill_background(game);
	x = 0;
	while (x < game->frame.width)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		finish_ray(game, &ray);
		draw_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}
