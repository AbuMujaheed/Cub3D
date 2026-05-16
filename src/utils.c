#include "cub3d.h"

int	is_space(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_blank(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	arg_has_cub(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}
