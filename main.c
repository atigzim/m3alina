# include "include/cub_3d.h"
bool tchick_wall(t_data *data, double y, double x)
{
    int map_x = (int)(x / TILE_SIZE);
    int map_y = (int)(y / TILE_SIZE);

    if (map_y < 0 || map_x < 0 ||
        map_y >= data->map_height ||
        map_x >= (int)ft_strlen(data->map[map_y]))
        return (true);

    if (data->map[map_y][map_x] == '1')
        return (true);

    return (false);
}

void turn_left(t_data *data)
{
    data->player.angle -= data->player.rotation_speed;
    if (data->player.angle > 2 * M_PI)
        data->player.angle -= 2 * M_PI;
    else if (data->player.angle < 0)
        data->player.angle += 2 * M_PI;
    data->player.dx -= cos(data->player.angle) * data->player.move_speed;
    data->player.dy -= sin(data->player.angle) * data->player.move_speed;
}

void turn_right(t_data *data)
{
    data->player.angle += data->player.rotation_speed;
    if (data->player.angle > 2 * M_PI)
        data->player.angle -= 2 * M_PI;
    else if (data->player.angle < 0)
        data->player.angle += 2 * M_PI;
    data->player.dx += cos(data->player.angle) * data->player.move_speed;
    data->player.dy += sin(data->player.angle) * data->player.move_speed;
}

void move_player(t_data *data, int key)
{
    double new_x = data->player.x;
    double new_y = data->player.y;

    if (key == W)
    {
        new_x += cos(data->player.angle) * data->player.move_speed;
        new_y += sin(data->player.angle) * data->player.move_speed;
    }
    else if (key == S)
    {
        new_x -= cos(data->player.angle) * data->player.move_speed;
        new_y -= sin(data->player.angle) * data->player.move_speed;
    }
    else if (key == A)
    {
        new_x += cos(data->player.angle - M_PI_2) * data->player.move_speed;
        new_y += sin(data->player.angle - M_PI_2) * data->player.move_speed;
    }
    else if (key == D)
    {
        new_x += cos(data->player.angle + M_PI_2) * data->player.move_speed;
        new_y += sin(data->player.angle + M_PI_2) * data->player.move_speed;
    }

    // if (key == LEFT)
    //     turn_left(data);
    // else if (key == RIGHT)
    //     turn_right(data);

    if (!tchick_wall(data, new_y, data->player.x))
        data->player.y = new_y;

    if (!tchick_wall(data, data->player.y, new_x))
        data->player.x = new_x;
}

int	key_press(int keycode, void *param)
{
    t_data *data = (t_data *)param;

    if (keycode == ESC)
    {
        // TODO: free_all(data) before exiting
        if (data && data->mlx)
            mlx_destroy_window(data->mlx, data->window);
        exit(0);
    }
    else
        move_player(data, keycode);
    return (0);
}

int	sed(void *param)
{
    t_data *data = (t_data *)param;
    (void)data;
    // TODO: free_all(data) before exiting
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
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	define_textures(data, fd);
	data->map_height = len_height(filename, data);
    add_map_line(data, filename);
	map_valid(new_map(data), data);
	close(fd);
}

int game_loop(t_data *data)
{
    draw_all(data);
    if (data && data->mlx && data->window && data->buffer.img_ptr)
        mlx_put_image_to_window(data->mlx, data->window,
            data->buffer.img_ptr, 0, 0);
    return (0);
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
    init_buffer(data);
    init_player(data);
    init_rays(data);
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
