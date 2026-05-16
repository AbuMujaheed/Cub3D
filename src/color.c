#include "cub3d.h"

static int	read_component(char **s, int *value)
{
	int	n;
	int	digits;

	while (is_space(**s))
		(*s)++;
	if (!ft_isdigit(**s))
		return (0);
	n = 0;
	digits = 0;
	while (ft_isdigit(**s))
	{
		n = n * 10 + **s - '0';
		if (n > 255)
			return (0);
		(*s)++;
		digits++;
	}
	*value = n;
	return (digits > 0);
}

int	parse_rgb(char *s, int *out)
{
	int	r;
	int	g;
	int	b;

	if (!read_component(&s, &r))
		return (0);
	while (is_space(*s))
		s++;
	if (*s++ != ',')
		return (0);
	if (!read_component(&s, &g))
		return (0);
	while (is_space(*s))
		s++;
	if (*s++ != ',')
		return (0);
	if (!read_component(&s, &b))
		return (0);
	while (is_space(*s))
		s++;
	if (*s)
		return (0);
	*out = (r << 16) | (g << 8) | b;
	return (1);
}
