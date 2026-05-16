#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define WIN_W 1024
# define WIN_H 768
# define TEX_N 0
# define TEX_S 1
# define TEX_W 2
# define TEX_E 3
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_cfg
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor;
	int		ceiling;
	int		has_floor;
	int		has_ceiling;
}	t_cfg;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		players;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	cam;
	double	dir_x;
	double	dir_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	wall;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_h;
	int		draw_s;
	int		draw_e;
	int		tex;
	int		tex_x;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		frame;
	t_img		tex[4];
	t_cfg		cfg;
	t_map		map;
	t_player	player;
	t_keys		keys;
}	t_game;

int		die(char *msg);
int		game_error(t_game *game, char *msg);
void	init_game(t_game *game);
void	free_split(char **tab);
void	free_game(t_game *game);
int		read_file(char *path, char **out);
int		parse_file(t_game *game, char *path);
int		parse_config(t_game *game, char **lines, int *i);
int		set_texture(t_game *game, char *line);
int		set_color(t_game *game, char *line);
int		parse_rgb(char *s, int *out);
int		build_map(t_game *game, char **lines, int start);
int		check_map(t_game *game);
int		find_player(t_game *game);
void	set_player_dir(t_player *p, char c);
int		setup_mlx(t_game *game);
void	load_textures(t_game *game);
int		close_game(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		loop_game(t_game *game);
void	move_player(t_game *game);
void	render(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	perform_dda(t_game *game, t_ray *ray);
void	finish_ray(t_game *game, t_ray *ray);
void	draw_column(t_game *game, t_ray *ray, int x);
void	put_pixel(t_img *img, int x, int y, int color);
int		get_pixel(t_img *img, int x, int y);
int		is_space(int c);
int		is_blank(char *line);
int		is_map_line(char *line);
char	*trim_nl(char *line);
int		max_int(int a, int b);
int		arg_has_cub(char *path);

#endif
