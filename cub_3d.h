#ifndef CUB_3D_3D
# define CUB_3D_3D

#include "libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_data
{
    char **map;
}t_data;


char	*get_next_line(int fd);
void	free_map(char **map);
void	exit_map(char **map);
int	    len_height(char *path_file);
void	loop_map(char *r_l_line, int fd, char **map, t_data *data);
char	**get_map(char *path_file, int len, t_data *data);
void	check_dot_ber(char *path_file, t_data *data);
void    parse_cub(char *filename, t_data *data);

#endif
