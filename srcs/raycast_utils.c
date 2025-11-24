/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:46:07 by abhmidat          #+#    #+#             */
/*   Updated: 2025/11/22 16:08:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void cast_one_ray(t_data *data, int ray_index)
{
    t_ray *ray = &data->rays[ray_index];

    double ray_angle = ray->ray_angle;
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);

    int map_x = (int)(data->player.x / TILE_SIZE);
    int map_y = (int)(data->player.y / TILE_SIZE);

    double side_dist_x;
    double side_dist_y;

    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    int step_x;
    int step_y;
    int hit = 0;
    int side; // 0 = vertical, 1 = horizontal

    // Calculate step and initial sideDist
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (data->player.x - map_x * TILE_SIZE) * delta_dist_x / TILE_SIZE;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((map_x + 1) * TILE_SIZE - data->player.x) * delta_dist_x / TILE_SIZE;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (data->player.y - map_y * TILE_SIZE) * delta_dist_y / TILE_SIZE;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((map_y + 1) * TILE_SIZE - data->player.y) * delta_dist_y / TILE_SIZE;
    }

    // DDA loop
    while (!hit)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }
        if (map_y < 0 || map_y >= data->map_height ||
            map_x < 0 || map_x >= (int)ft_strlen(data->map[map_y]))
            break;
        if (data->map[map_y][map_x] == '1')
            hit = 1;
    }

    // Calculate distance to wall
    double perp_wall_dist;
    if (hit)
    {
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x) * TILE_SIZE;
        else
            perp_wall_dist = (side_dist_y - delta_dist_y) * TILE_SIZE;
        ray->distance = perp_wall_dist;
        ray->is_vertical_hit = (side == 0);
        // Optionally store hit position:
        ray->ray_x = data->player.x + ray->distance * ray_dir_x;
        ray->ray_y = data->player.y + ray->distance * ray_dir_y;
    }
}
// void walls_parameters(t_ray *ray)
// {
//     int iter;

//     iter = 0;
//     while(iter < WIN_WIDTH - 2)
//     {
//         if (ray[iter].is_vertical_hit == 1 && ray[iter + 2].is_vertical_hit == 2)
//         {
            
//         }
//         iter++;
//     }
// }
void render_walls(t_data *data)
{
    int i;
    int y;
    t_ray *ray;
    t_walls *wall;

    i = 0;
    wall = &data->wall;
    while (i < WIN_WIDTH)
    {
        ray = &data->rays[i];
        ray->distance = ray->distance;
        wall->corrected_dist = ray->distance *
                cos(ray->ray_angle - data->player.angle);
        wall->distance_to_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
        if (wall->corrected_dist <= 0.0001)
            wall->corrected_dist = 0.0001;
        wall->wall_height = (TILE_SIZE / wall->corrected_dist) * wall->distance_to_plane;
        wall->wall_start = (WIN_HEIGHT / 2) - (wall->wall_height / 2);
        wall->wall_end = (WIN_HEIGHT / 2) + (wall->wall_height / 2);
        if (wall->wall_start < 0)
            wall->wall_start = 0;
        if (wall->wall_end >= WIN_HEIGHT)
            wall->wall_end = WIN_HEIGHT - 1;
        y = wall->wall_start;
        while (y <= wall->wall_end)
        {
            my_mlx_pixel_put(&data->buffer, i, y, 0xAAAAAA);
            y++;
        }
        i++;
    }
}
// void draw_C_F(t_data *data)
// {
//     int i;
//     int y;

//     i = 0;
//     while (i < WIN_HEIGHT)
//     {
//         y = 0;
//         while (y < WIN_WIDTH)
//         {
//             if (i < WIN_HEIGHT / 2)
//                 my_mlx_pixel_put(&data->buffer, y, i, 0x87CEEB);
//             else
//                 my_mlx_pixel_put(&data->buffer, y, i, 0x78461E);
//             y++;
//         }
//         i++;
//     }
// }

void draw_all(t_data *data)
{
    int i;
    int y;

    i = 0;

    while (i < WIN_WIDTH)
    {
        y = 0;
        while (y < WIN_HEIGHT)
        {
            my_mlx_pixel_put(&data->buffer, i, y, 0x000000);
            y++;
        }
        i++;
    }
    grid_lines(data);
    // draw_C_F(data);
    cast_all_rays(data);
    render_walls(data); // <-- UNCOMMENTED: walls are now rendered
}
void cast_all_rays(t_data *data)
{
    int i = 0;
    while (i < WIN_WIDTH)
    {
        data->rays[i].ray_angle = data->player.angle - (FOV / 2) + (i * (FOV / (double)WIN_WIDTH));
        cast_one_ray(data, i);
        i++;
    }
}
