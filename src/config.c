#include "cub3d.h"

static char	*skip_id(char *line)
{
	line += 2;
	while (is_space(*line))
		line++;
	return (line);
}

static char	*dup_path(char *line)
{
	char	*start;
	char	*end;
	char	*out;
	int		len;

	start = skip_id(line);
	end = start + ft_strlen(start);
	while (end > start && is_space(*(end - 1)))
		end--;
	len = (int)(end - start);
	if (len <= 0)
		return (NULL);
	out = ft_substr(start, 0, len);
	return (out);
}

static int	assign_path(char **dst, char *line)
{
	if (*dst)
		return (0);
	*dst = dup_path(line);
	return (*dst != NULL);
}

int	set_texture(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (assign_path(&game->cfg.north, line));
	if (!ft_strncmp(line, "SO ", 3))
		return (assign_path(&game->cfg.south, line));
	if (!ft_strncmp(line, "WE ", 3))
		return (assign_path(&game->cfg.west, line));
	if (!ft_strncmp(line, "EA ", 3))
		return (assign_path(&game->cfg.east, line));
	return (0);
}

int	set_color(t_game *game, char *line)
{
	int	color;
	char	*value;

	value = line + 1;
	while (is_space(*value))
		value++;
	if (!parse_rgb(value, &color))
		return (0);
	if (!ft_strncmp(line, "F ", 2) && !game->cfg.has_floor)
	{
		game->cfg.floor = color;
		game->cfg.has_floor = 1;
		return (1);
	}
	if (!ft_strncmp(line, "C ", 2) && !game->cfg.has_ceiling)
	{
		game->cfg.ceiling = color;
		game->cfg.has_ceiling = 1;
		return (1);
	}
	return (0);
}
