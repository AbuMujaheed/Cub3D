/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:42:22 by sojetimi          #+#    #+#             */
/*   Updated: 2026/06/04 12:42:23 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (die("Usage: ./cub3D maps/example.cub"));
	init_game(&game);
	if (!parse_file(&game, argv[1]))
		return (game_error(&game, "Invalid cub file"));
	if (!setup_mlx(&game))
		return (game_error(&game, "MLX setup failed"));
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx, loop_game, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
// norminette libft, src, include