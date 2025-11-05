#ifndef CUB_3D_3D
# define CUB_3D_3D

#include "libft/libft.h"
# include <math.h>
// # include <mlx.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_textures {
    char *north;
    char *south;
    char *west;
    char *east;
} t_textures;
typedef struct s_data
{
    char **map;
    int plyar_x;
    int plyar_y;
    int map_width;
    int map_height;
    char *floor;
    char *ceiling;
    t_textures textures;
}t_data;


char	*get_next_line(int fd);
void	free_map(char **map);
void	exit_map(char **map);
int	len_height(char *filename, t_data *data);
char	*skip_spacess(char *line);
int	check_textures(char *line);
char	*find_path(char *line, char *identifier);
char	*find_int(char *line);
void	loop_map(char *r_l_line, int fd, char **map, t_data *data);
// char	**get_map(int fd, int len, t_data *data);
void	has_cub_extension(char *path_file, t_data *data);
void    parse_cub(char *filename, t_data *data);

#endif
