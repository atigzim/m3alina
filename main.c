# include "include/cub_3d.h"

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

void init_player(t_data *data)
{
    data->player.move_speed = 3;
    data->player.rotation_speed = 0.09;
	data->player.x = data->player_x*TILE_SIZE + (TILE_SIZE /2);
	data->player.y = data->player_y *TILE_SIZE + (TILE_SIZE /2);
    if (data->player_dir == 'N')
        data->player.angle = -M_PI / 2;
    else if (data->player_dir == 'S')
        data->player.angle = M_PI / 2;
    else if (data->player_dir == 'W')
        data->player.angle = M_PI;
    else
        data->player.angle = 0;
}

void draw_player_position(t_data *data)
{
    int player_screen_x = (int)data->player.x;  // Already calculated in init_player
    int player_screen_y = (int)data->player.y;
    for (int i = -8; i <= 8; i++)
    {
        for (int j = -8; j <= 8; j++)
        {
            int px = player_screen_x + j;
            int py = player_screen_y + i;
            if (px >= 0 && px < WIN_WIDTH && py >= 0 && py < WIN_HEIGHT)
                my_mlx_pixel_put(&data->buffer, px, py, 0xFFFFFF);
        }
    }
}

// void shoot_ray_from_position(t_data *data, int start_x, int start_y, double angle, int color)
// {
//     double ray_x = start_x;
//     double ray_y = start_y;
    
//     double step_x = cos(angle);
//     double step_y = sin(angle);
    
//     int distance = 0;
//     int max_distance = 1000;
    
//     while (distance < max_distance)
//     {
//         ray_x += step_x;
//         ray_y += step_y;
        
//         int px = (int)ray_x;
//         int py = (int)ray_y;
        
//         if (px < 0 || px >= WIN_WIDTH || py < 0 || py >= WIN_HEIGHT)
//             break;
        
//         int grid_x = px / TILE_SIZE;
//         int grid_y = py / TILE_SIZE;
        
//         if (grid_x >= 0 && grid_x < data->map_width &&
//             grid_y >= 0 && grid_y < data->map_height)
//         {
//             if (data->map[grid_y][grid_x] == '1')
//             {
//                 // Hit wall - draw marker
//                 for (int i = -3; i <= 3; i++)
//                 {
//                     for (int j = -3; j <= 3; j++)
//                     {
//                         int hx = px + j;
//                         int hy = py + i;
//                         if (hx >= 0 && hx < WIN_WIDTH && hy >= 0 && hy < WIN_HEIGHT)
//                             my_mlx_pixel_put(&data->buffer, hx, hy, 0xFFFFFF);
//                     }
//                 }
//                 break;
//             }
//         }
        
//         // Draw ray
//         for (int i = -1; i <= 1; i++)
//         {
//             for (int j = -1; j <= 1; j++)
//             {
//                 int dx = px + j;
//                 int dy = py + i;
//                 if (dx >= 0 && dx < WIN_WIDTH && dy >= 0 && dy < WIN_HEIGHT)
//                     my_mlx_pixel_put(&data->buffer, dx, dy, color);
//             }
//         }
        
//         distance++;
//     }
// }


void draw_block(t_image *img, int x, int y, int cool)
{
	int i;
	int j ;

	j = x;
	while (j < x + 4)
	{
		i = y;
		while (i < y + 4)
		{
			my_mlx_pixel_put(img, j, i, cool);
			i++;
		}
		j++;
	}
}

// void draw_background(t_data *data)
// {
// 	t_image *img;
// 	int y;
// 	int i;

// 	i = 0;
// 	img = &data->buffer;
// 	while(data->map[i])
// 	{
// 		y = 0;
// 		while(data->map[i][y])
// 		{
// 			if(data->map[i][y] == '1')
// 				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
// 			else if(data->map[i][y] != '0' && data->map[i][y] != '1')
// 				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0x00FF00);
// 			y++;
// 		}
// 		i++;
// 	}
	
// }
void grid_lines(t_data *data)
{
    int x = 0;
    int y = 0;

    while(x < WIN_WIDTH)
    {
        y = 0;
        while(y < WIN_HEIGHT)
        {
            if(x % TILE_SIZE == 0 || y % TILE_SIZE == 0)
                my_mlx_pixel_put(&data->buffer, x, y, 0xFFFFFF);
            if(x == (int)data->player.x && y == (int)data->player.y)
                draw_block(&data->buffer, x - 2, y - 2, 0xFF0000);
            y ++;
        }
        x ++;
    }
}
void init_rays(t_data *data)
{
    int i = 0;
    while (i < WIN_WIDTH)
    {
        data->rays[i].ray_angle = data->player.angle - (FOV / 2) + (i * (FOV / WIN_WIDTH));
        i++;
    }
}
void cast_one_ray(t_data *data, int ray_index)
{
    t_ray *ray = &data->rays[ray_index];

    int iter = 0;
    ray->start_x = data->player.x;
    ray->start_y = data->player.y;

    ray->ray_x = ray->start_x;
    ray->ray_y = ray->start_y;
    ray->step_x = cos(ray->ray_angle);
    ray->step_y = sin(ray->ray_angle);

    while ( iter < MAX_DESTINATIONS)
    {
        ray->ray_x += ray->step_x;
        ray->ray_y += ray->step_y;
        ray->grid_x = ray->ray_x / TILE_SIZE;
        ray->grid_y = ray->ray_y / TILE_SIZE;
        if (ray->grid_y < 0 || ray->grid_y >= data->map_height ||
            ray->grid_x < 0 || ray->grid_x >= data->map_width)
            break;
        if (data->map[ray->grid_y][ray->grid_x] == '1')
        {
            ray->wall_hit_x = ray->ray_x;
            ray->wall_hit_y = ray->ray_y;
            ray->dx = ray->ray_x - ray->start_x;
            ray->dy = ray->ray_y - ray->start_y;
            ray->distance = sqrt(ray->dx * ray->dx + ray->dy * ray->dy);
            ray->is_vertical_hit = (fabs(ray->step_x) > fabs(ray->step_y));
            return;
        }
        my_mlx_pixel_put(&data->buffer,
            (int)ray->ray_x, (int)ray->ray_y, 0x00FF00);
        iter++;
    }
}

void cast_all_rays(t_data *data)
{
    int i = 0;
    while (i < WIN_WIDTH)
    {
        cast_one_ray(data, i);
        i++;
    }
}

int game_loop(t_data *data)
{
    grid_lines(data);
    cast_all_rays(data);
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
