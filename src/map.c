#include "cub3d.h"

static int	map_height(char **lines, int start)
{
	int	h;

	h = 0;
	while (lines[start + h])
		h++;
	return (h);
}

static int	map_width(char **lines, int start)
{
	int	w;
	int	i;

	w = 0;
	i = start;
	while (lines[i])
	{
		if (!is_map_line(lines[i]))
			return (-1);
		w = max_int(w, (int)ft_strlen(lines[i]));
		i++;
	}
	return (w);
}

static char	*pad_line(char *line, int width)
{
	char	*out;
	int		i;

	out = malloc(width + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (line[i])
	{
		out[i] = line[i];
		i++;
	}
	while (i < width)
		out[i++] = ' ';
	out[i] = '\0';
	return (out);
}

int	build_map(t_game *game, char **lines, int start)
{
	int	i;

	game->map.height = map_height(lines, start);
	game->map.width = map_width(lines, start);
	if (game->map.height <= 0 || game->map.width <= 0)
		return (0);
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = pad_line(lines[start + i], game->map.width);
		if (!game->map.grid[i])
			return (0);
		i++;
	}
	return (1);
}

int	check_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.grid[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				if (y == 0 || x == 0 || y == game->map.height - 1
					|| x == game->map.width - 1
					|| game->map.grid[y - 1][x] == ' '
					|| game->map.grid[y + 1][x] == ' '
					|| game->map.grid[y][x - 1] == ' '
					|| game->map.grid[y][x + 1] == ' ')
					return (0);
			x++;
		}
		y++;
	}
	return (game->map.players == 1);
}
