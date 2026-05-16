#include "cub3d.h"

static void	load_one(t_game *game, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->img)
		game_error(game, "Texture load failed");
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		game_error(game, "Texture data failed");
}

void	load_textures(t_game *game)
{
	load_one(game, &game->tex[TEX_N], game->cfg.north);
	load_one(game, &game->tex[TEX_S], game->cfg.south);
	load_one(game, &game->tex[TEX_W], game->cfg.west);
	load_one(game, &game->tex[TEX_E], game->cfg.east);
}

int	setup_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
		return (0);
	game->frame.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->frame.img)
		return (0);
	game->frame.addr = mlx_get_data_addr(game->frame.img,
			&game->frame.bpp, &game->frame.line_len, &game->frame.endian);
	if (!game->frame.addr)
		return (0);
	game->frame.width = WIN_W;
	game->frame.height = WIN_H;
	load_textures(game);
	return (1);
}
