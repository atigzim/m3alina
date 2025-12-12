/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 00:27:33 by atigzim           #+#    #+#             */
/*   Updated: 2025/12/13 00:42:07 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include <mlx.h>
# include "../libft/libft.h"
# include <math.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 64
# define WIN_WIDTH 1000
# define WIN_HEIGHT 600
# define CLOSE 17
# define PI 3.1415926535
# define TWO_PI 6.283185307
# define FOV 1.0471975512
# define MAX_DESTINATIONS 1000

typedef enum e_key
{
	ESC = 65307,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	LEFT = 65361,
	RIGHT = 65363,
	UP = 65362,
	DOWN = 65364,
	SPACE = 32,
	F_Key = 102,
}					t_key;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_flags
{
	int	north;
	int	south;
	int	west;
	int	east;
	int	floor;
	int	ceiling;
}	t_flags;

typedef struct s_image
{
	void	*img_ptr;
	char	*pixel_data;
	int		bpp;
	int		endian;
	int		line_size;
	int		width;
	int		height;
}	t_image;

typedef struct s_ray
{
	double	distance;
	double	ray_angle;
	int		map_x;
	int		map_y;
	double	ray_x;
	double	ray_y;
	double	step_x;
	double	step_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	dx;
	double	dy;
	int		hit;
	int		is_vertical_hit;
}	t_ray;

typedef struct s_walls
{
	double	corrected_dist;
	double	distance_to_plane;
	int		wall_height;
	int		wall_start;
	int		wall_end;
}	t_walls;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	radius;
	double	angle;
	double	rotation_speed;
	double	move_speed;
	char	direction;
}	t_player;

typedef struct s_data
{
	char		**map;
	char		player_dir;
	int			player_x;
	int			player_y;
	int			map_width;
	int			map_height;
	int			floor_color;
	int			ceiling_color;
	void		*mlx;
	void		*window;
	t_image		buffer;
	t_textures	textures;
	t_image		tex_no;
	t_image		tex_so;
	t_image		tex_we;
	t_image		tex_ea;
	t_player	player;
	t_ray		rays[WIN_WIDTH];
	t_walls		wall;
	t_flags		flags;
	t_color		f_c_color;
}	t_data;

//parsing
char	*get_next_line(int fd);
char	*strip_newline(char *line);
bool	ft_isspace(char c);
int		len_height(char *filename, t_data *data, int *offset);
bool	search_map(char *line);
char	*skip_spacess(char *line);
bool	check_textures(char *line);
char	*find_path(char *line, char *position, t_data *data,
			char *original_line);
int		parse_color_to_int(char *line, t_data *data, char *original_line);
void	has_cub_extension(char *path_file, t_data *data);
void	parse_cub(char *filename, t_data *data);
void	define_textures(t_data *data, int fd, int *offset);
void	free_all_and_print_error(t_data *data, char **map, char *line);
char	*padd_line(char *line, int len, t_data *data, char **ne_map);
char	**new_map(t_data *data, int fd);
void	map_valid(char **map, t_data *data);
void	add_map_line(t_data *data, char *filename);
bool	check_wall(t_data *data, int lne, int i, int j);
bool	check_out(char **map, int i, int j);
void	check_valid_character(char c, t_data *data, char **map);
void	player_position(t_data *data, int i, int j);
void	pars_textures(char *line, t_data *data, int *offset);
void	one_line_map(t_data *data, int fd, char *line);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
bool	xpm_valid(char *path_file);
void	parse_xpm(t_data *data);
void	pars_main(t_data *data, char *filename);
void	check_map_valid(char **map, t_data *data, int i, int j);
//raycasting
void	grid_lines(t_data *data);
void	draw_block(t_image *img, int x, int y, int cool);
void	draw_all(t_data *data);
int		game_loop(t_data *data);
int		key_press(int keycode, void *param);
int		sed(void *param);
//cast rays
void	cast_one_ray(t_data *data, int ray_index);
void	cast_all_rays(t_data *data);
void	render_walls(t_data *data);
//init all
void	init_player(t_data *data);
void	init_rays(t_data *data);
void	init_buffer(t_data *mlx);
//move player
bool	tchick_wall(t_data *data, double y, double x);
void	move_player(t_data *data, int key);
void	turn_left(t_data *data);
void	turn_right(t_data *data);
//free all
void	free_data(t_data *data);
void	free_map(char **map);
void	free_mlx(t_data *data);
//textures
int		load_texture(t_data *data, t_image *tex, char *path);
int		texture_get_pixel(t_image *tex, int x, int y);
int		set_textures(t_data *data);
t_image	*texture_decide(t_data *data, t_ray *ray);
void	draw_wall(t_data *data, int ray_index, double wall_top,
			double wall_bottom);
void	put_pixel_to_buffer(t_image *buffer, int x, int y, int color);

#endif
