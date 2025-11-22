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
    int iter;

    iter = 0;
    ray->start_x = data->player.x;
    ray->start_y = data->player.y;

    ray->ray_x = ray->start_x;
    ray->ray_y = ray->start_y;
    ray->step_x = cos(ray->ray_angle);
    ray->step_y = sin(ray->ray_angle);

    while (iter < MAX_DESTINATIONS)
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
        // my_mlx_pixel_put(&data->buffer,
        //     (int)ray->ray_x, (int)ray->ray_y, 0x00FF00);
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
void draw_C_F(t_data *data)
{
    int i;
    int y;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        y = 0;
        while (y < WIN_WIDTH)
        {
            if (i < WIN_HEIGHT / 2)
                my_mlx_pixel_put(&data->buffer, y, i, 0x87CEEB);
            else
                my_mlx_pixel_put(&data->buffer, y, i, 0x78461E);
            y++;
        }
        i++;
    }
}

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
    // grid_lines(data);
    draw_C_F(data);
    cast_all_rays(data);
    render_walls(data);
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
