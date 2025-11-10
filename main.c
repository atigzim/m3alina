#include "cub_3d.h"

void parse_cub(char *filename, t_data *data)
{
    int fd;

    has_cub_extension(filename, data);
    fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		//free_all
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	define_textures(data, fd);
	data->map_height = len_height(filename, data);
    add_map_line(data, filename);
	map_valid(new_map(data), data);
	close(fd);
}

int main(int ac, char *av[])
{
    t_data  *data;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }
	data = malloc(sizeof(t_data)); 
	if(!data)
		return(1);
	ft_bzero(data, sizeof(t_data));
    parse_cub(av[1], data);

	data->mlx = mlx_init();
	if(!data->mlx)
	{
		//free_all;
		return (1);
	}
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	// init_buffer(data);
	// init_player(data);
	// mlx_hook(data->window, 2, 1L << 0, key_press, data);
	// mlx_hook(data->window, 17, 0, sed, data);
	// mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
