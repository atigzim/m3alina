#ifndef CUB_3D_3D
# define CUB_3D_3D

// # include <mlx.h> 
#include "../minilibx-linux/mlx.h"
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

# define TILE_SIZE 32 // Makes map fit in window
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define CLOSE 17
# define PI 3.1415926535
# define TWO_PI 6.283185307 // represents a full 360° circle in radians.
# define FOV 1.0471975512 // 60° in radians
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

typedef struct s_textures {
    char *north;
    char *south;
    char *west;
    char *east;
} t_textures;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_flags
{
   int	north;
   int	south;
   int	west;
   int	east;
   int	floor;
   int	ceiling;
}				t_flags;

typedef struct s_image
{
	void		*img_ptr;
	char		*pixel_data;
	int			bpp;
	int			endian;
	int			line_size;
	int			width;
	int			height;
}    t_image;


typedef struct s_ray
{
    double distance;
    double ray_angle;
    double ray_x;
    double ray_y;
    double step_x;
    double step_y;
    int grid_x;
    int grid_y;
    double dx;
    double dy;
    double start_x;
    double start_y;
    int is_vertical_hit;   // 1 = vertical wall, 2 = horizontal wall
} t_ray;

typedef struct s_walls
{
    double corrected_dist;
    double distance_to_plane;
    int wall_height;
    int wall_start;
    int wall_end;
}t_walls;

typedef struct s_player
{
    double        x;
    double        y;
    double        dx;
    double        dy;
    double        radius;
    double        angle;
    double        rotation_speed;
    double        move_speed;
    char        direction;
}                t_player;

typedef struct s_data
{
    char **map;
    char player_dir;
    int player_x;
    int player_y;
    int map_width;
    int map_height;
    int floor_color;
    int ceiling_color;
    void *mlx;
    void *window;
    t_image buffer;
    t_textures textures;
    t_player player;
    t_ray    rays[WIN_WIDTH];
    t_walls wall;
    t_flags flags;
    t_color f_c_color;
}   t_data;

char	*get_next_line(int fd);
char *strip_newline(char *line);
bool	ft_isspace(char c);
int	len_height(char *filename, t_data *data, int *offset);
bool	search_map(char *line);
char	*skip_spacess(char *line);
bool check_textures(char *line);
char *find_path(char *line, char *position, t_data *data);
int parse_color_to_int(char *line, t_data *data);
void	has_cub_extension(char *path_file, t_data *data);
void    parse_cub(char *filename, t_data *data);
void define_textures(t_data *data, int fd, int *offset);
void free_all_and_print_error(t_data *data, char **map);
char *padd_line(char *line, int len);
char **new_map(t_data *data);
void map_valid(char **map, t_data *data);
void add_map_line(t_data *data, char *filename);
bool check_wall(t_data *data, int lne, int i, int j);
bool check_out(char **map, int i, int j);
void check_valid_character(char c, t_data *data, char **map);

//raycast

void cast_rays(t_data *data);
int pos_is_wall(t_data *data, double dx, double dy);
int direction_check(double angle, char c);
int view_check(double angle, double *inter, double *step, int is_horz);
double update_angle(double angle);
double calc_distance(double x1, double x2, double y1, double y2);
void draw_3d_wall_strip(t_data *data, int strip_id);
void grid_lines(t_data *data);
void init_rays(t_data *data);
void draw_block(t_image *img, int x, int y, int cool);
void cast_one_ray(t_data *data, int ray_index);
void render_walls(t_data *data);
void draw_all(t_data *data);
void cast_all_rays(t_data *data);
void init_player(t_data *data);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
void init_buffer(t_data *mlx);
int find_int(char *line);

#endif
