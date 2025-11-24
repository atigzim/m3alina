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

void cast_one_ray_v(t_data *data, int ray_index)
{
    t_ray *ray = &data->rays[ray_index];
    int iter;

    iter = 0;
    ray->ray_v.start_x = data->player.x;
    ray->ray_v.start_y = data->player.y;
    ray->ray_v.ray_x = ray->ray_v.start_x;
    ray->ray_v.ray_y = ray->ray_v.start_y;
    ray->ray_v.step_x = cos(ray->ray_angle);
    ray->ray_v.step_y = sin(ray->ray_angle);
    
    while (iter < MAX_DESTINATIONS)
    {
        ray->ray_v.ray_x += ray->ray_v.step_x;
        ray->ray_v.ray_y += ray->ray_v.step_y;
        ray->ray_v.grid_x = ray->ray_v.ray_x / TILE_SIZE;
        ray->ray_v.grid_y = ray->ray_v.ray_y / TILE_SIZE;
        if (ray->ray_v.grid_y < 0 || ray->ray_v.grid_y >= data->map_height ||
            ray->ray_v.grid_x < 0 || ray->ray_v.grid_x >= (int)ft_strlen(data->map[ray->ray_v.grid_y]))
            break;
        if(ray->ray_v.ray_x >= WIN_WIDTH || ray->ray_v.ray_y >= WIN_HEIGHT || ray->ray_v.ray_x < 0 || ray->ray_v.ray_y < 0)
            break;
        if (data->map[ray->ray_v.grid_y][ray->ray_v.grid_x] == '1' && (int)ray->ray_v.ray_x % TILE_SIZE == 0)
        {
            ray->ray_v.dx = ray->ray_v.ray_x - ray->ray_v.start_x;
            ray->ray_v.dy = ray->ray_v.ray_y - ray->ray_v.start_y;
            ray->ray_v.distance = sqrt(ray->ray_v.dx * ray->ray_v.dx + ray->ray_v.dy * ray->ray_v.dy);
        }
        my_mlx_pixel_put(&data->buffer,
            (int)ray->ray_v.ray_x, (int)ray->ray_v.ray_y, 0x0000FF);
        iter++;
    }
}
void cast_one_ray_h(t_data *data, int ray_index)
{
    t_ray *ray = &data->rays[ray_index];
    int iter;

    iter = 0;
    ray->ray_h.start_x = data->player.x;
    ray->ray_h.start_y = data->player.y;
    ray->ray_h.ray_x = ray->ray_h.start_x;
    ray->ray_h.ray_y = ray->ray_h.start_y;
    ray->ray_h.step_x = cos(ray->ray_angle);
    ray->ray_h.step_y = sin(ray->ray_angle);

    while (iter < MAX_DESTINATIONS)
    {
        ray->ray_h.ray_x += ray->ray_h.step_x;
        ray->ray_h.ray_y += ray->ray_h.step_y;
        ray->ray_h.grid_x = ray->ray_h.ray_x / TILE_SIZE;
        ray->ray_h.grid_y = ray->ray_h.ray_y / TILE_SIZE;
        if (ray->ray_h.grid_y < 0 || ray->ray_h.grid_y >= data->map_height ||
            ray->ray_h.grid_x < 0 || ray->ray_h.grid_x >= (int)ft_strlen(data->map[ray->ray_h.grid_y]))
            break;
        if(ray->ray_h.ray_x >= WIN_WIDTH || ray->ray_h.ray_y >= WIN_HEIGHT || ray->ray_h.ray_x < 0 || ray->ray_h.ray_y < 0)
            break;
        if (data->map[ray->ray_h.grid_y][ray->ray_h.grid_x] == '1' && (int)ray->ray_h.ray_y % TILE_SIZE == 0)
        {
            ray->ray_h.dx = ray->ray_h.ray_x - ray->ray_h.start_x;
            ray->ray_h.dy = ray->ray_h.ray_y - ray->ray_h.start_y;
            ray->ray_h.distance = sqrt(ray->ray_h.dx * ray->ray_h.dx + ray->ray_h.dy * ray->ray_h.dy);
            return;
        }
        my_mlx_pixel_put(&data->buffer,
            (int)ray->ray_h.ray_x, (int)ray->ray_h.ray_y, 0x00FF00);
        iter++;
    }
}
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
        printf(" ray->ray_v.distance %f,ray->ray_h.distance %f \n", ray->ray_v.distance, ray->ray_h.distance);
        if (ray->ray_v.distance < ray->ray_h.distance)
        {
            printf(" i = %d ,ray->ray_v.distance %f \n", i, ray->distance);
            ray->distance = ray->ray_v.distance;
            ray->is_vertical_hit = 1;
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
        }
        else
        {
            printf(" i = %d ,ray->ray_h.distance  %f \n", i, ray->distance);
            ray->distance = ray->ray_h.distance;
            ray->is_vertical_hit = 0;
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
        }
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
    render_walls(data);
}
void cast_all_rays(t_data *data)
{
    int i = 0;
    while (i < WIN_WIDTH)
    {
        data->rays[i].ray_angle = data->player.angle - (FOV / 2) + (i * (FOV / (double)WIN_WIDTH));
        cast_one_ray_v(data, i);
        cast_one_ray_h(data, i);
        i++;
    }
}
