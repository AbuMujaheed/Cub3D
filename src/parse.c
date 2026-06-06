/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:31:58 by sojetimi          #+#    #+#             */
/*   Updated: 2026/06/04 12:42:39 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	config_done(t_game *game)
{
	return (game->cfg.north && game->cfg.south && game->cfg.west
		&& game->cfg.east && game->cfg.has_floor && game->cfg.has_ceiling);
}

int	parse_config(t_game *game, char **lines, int *i)
{
	while (lines[*i])
	{
		if (is_blank(lines[*i]))
			(*i)++;
		else if (!ft_strncmp(lines[*i], "NO ", 3)
			|| !ft_strncmp(lines[*i], "SO ", 3)
			|| !ft_strncmp(lines[*i], "WE ", 3)
			|| !ft_strncmp(lines[*i], "EA ", 3))
		{
			if (!set_texture(game, lines[*i]))
				return (0);
			(*i)++;
		}
		else if (!ft_strncmp(lines[*i], "F ", 2)
			|| !ft_strncmp(lines[*i], "C ", 2))
		{
			if (!set_color(game, lines[*i]))
				return (0);
			(*i)++;
		}
		else
			break ;
	}
	return (config_done(game));
}

int	parse_file(t_game *game, char *path)
{
	char	*text;
	char	**lines;
	int		i;
	int		ok;

	if (!arg_has_cub(path) || !read_file(path, &text))
		return (0);
	lines = ft_split(text, '\n');
	free(text);
	if (!lines)
		return (0);
	i = 0;
	ok = parse_config(game, lines, &i);
	while (ok && lines[i] && is_blank(lines[i]))
		i++;
	if (ok)
		ok = build_map(game, lines, i);
	free_split(lines);
	if (!ok)
		return (0);
	return (find_player(game) && check_map(game));
}
