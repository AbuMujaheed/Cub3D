#include "cub3d.h"

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->cfg.floor = -1;
	game->cfg.ceiling = -1;
}

void	free_game(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->mlx && game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
	if (game->mlx && game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game->cfg.north);
	free(game->cfg.south);
	free(game->cfg.west);
	free(game->cfg.east);
	free_split(game->map.grid);
}
