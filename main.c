#include "cub_3d.h"

void init_buffer(t_data *mlx)
{
	mlx->buffer.img_ptr = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->buffer.width =  WIN_WIDTH;
	mlx->buffer.height =  WIN_HEIGHT;
	mlx->buffer.pixel_data = mlx_get_data_addr(
        mlx->buffer.img_ptr, &mlx->buffer.bpp,
        &mlx->buffer.line_size, &mlx->buffer.endian);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    dst = img->pixel_data + (y * img->line_size + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}
void draw_block(t_image *img, int x, int y, int cool)
{
	int i;
	int j ;

	j = x;
	while (j < x + TILE_SIZE)
	{
		i = y;
		while (i < y + TILE_SIZE)
		{
			my_mlx_pixel_put(img, j, i, cool);
			i++;
		}
		j++;
	}
}

int	key_press(int keycode)
{
	if (keycode == ESC)
	{
		//free_all
		exit(0);
	}
	// if (keycode == D || keycode == 65363)
	// 	mov_right(mlx);
	// else if (keycode == W || keycode == 65362)
	// 	mov_up(mlx);
	// else if (keycode == A || keycode == 65361)
	// 	mov_left(mlx);
	// else if (keycode == S || keycode == 65364)
	// 	mov_down(mlx);
	return (0);
}

int	sed(t_data *mlx)
{
	//feer_all
	(void)mlx;
	exit(0);
	return (0);
}

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

	// data->mlx = mlx_init();
	// if(!data->mlx)
	// {
	// 	//free_all;
	// 	return (1);
	// }
	// data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
	// 		 WIN_HEIGHT , "Cub_3D");
	// init_buffer(data);
	// // init_player(data);
	// mlx_hook(data->window, 2, 1L << 0, key_press, data);
	// mlx_hook(data->window, 17, 0, sed, data);
	// // mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	// mlx_loop(data->mlx);
}
