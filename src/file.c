/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojetimi <sojetimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:29:59 by sojetimi          #+#    #+#             */
/*   Updated: 2026/06/04 12:42:14 by sojetimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	append_buf(char **text, char *buf, int n)
{
	char	*part;
	char	*joined;

	buf[n] = '\0';
	part = ft_strdup(buf);
	if (!part)
		return (0);
	joined = ft_strjoin(*text, part);
	free(part);
	free(*text);
	if (!joined)
		return (0);
	*text = joined;
	return (1);
}

int	read_file(char *path, char **out)
{
	char	buf[1025];
	int		fd;
	int		n;

	*out = ft_strdup("");
	if (!*out)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(*out), *out = NULL, 0);
	n = read(fd, buf, 1024);
	while (n > 0)
	{
		if (!append_buf(out, buf, n))
			return (close(fd), free(*out), *out = NULL, 0);
		n = read(fd, buf, 1024);
	}
	close(fd);
	if (n < 0)
		return (free(*out), *out = NULL, 0);
	return (1);
}
