/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:46:07 by abhmidat          #+#    #+#             */
/*   Updated: 2025/12/11 19:43:40 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	find_step_and_side_dist(t_data *data, t_ray *ray)
{
	if (ray->dx < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x * TILE_SIZE)
			/ fabs(ray->dx);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1) * TILE_SIZE - data->player.x)
			/ fabs(ray->dx);
	}
	if (ray->dy < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y * TILE_SIZE)
			/ fabs(ray->dy);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1) * TILE_SIZE - data->player.y)
			/ fabs(ray->dy);
	}
}

void	loop_for_wall_hit(t_data *data, t_ray *ray, int *hit)
{
	while (!*hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->map_x += ray->step_x;
			ray->is_vertical_hit = 0;
			ray->side_dist_x += ray->delta_dist_x;
		}
		else
		{
			ray->map_y += ray->step_y;
			ray->is_vertical_hit = 1;
			ray->side_dist_y += ray->delta_dist_y;
		}
		if (ray->map_y < 0 || ray->map_y >= data->map_height
			|| ray->map_x < 0
			|| ray->map_x >= (int)ft_strlen(data->map[ray->map_y]))
			break ;
		if (data->map[ray->map_y][ray->map_x] == '1')
			*hit = 1;
	}
}

void	calculate_distance_to_wall(t_data *data, t_ray *ray
		, int ray_index, int *hit)
{
	if (*hit)
	{
		if (ray->is_vertical_hit == 0)
			ray->distance = ray->side_dist_x - ray->delta_dist_x;
		else
			ray->distance = ray->side_dist_y - ray->delta_dist_y;
		ray->is_vertical_hit = (data->rays[ray_index].is_vertical_hit == 0);
		ray->ray_x = data->player.x + ray->distance * ray->dx;
		ray->ray_y = data->player.y + ray->distance * ray->dy;
	}
}

void	cast_one_ray(t_data *data, int ray_index)
{
	int			hit;
	t_ray		*ray;

	hit = 0;
	ray = &data->rays[ray_index];
	ray->dx = cos(ray->ray_angle);
	ray->dy = sin(ray->ray_angle);
	if (ray->dx == 0)
		ray->dx = 0.000001;
	if (ray->dy == 0)
		ray->dy = 0.000001;
	ray->map_x = (int)(data->player.x / TILE_SIZE);
	ray->map_y = (int)(data->player.y / TILE_SIZE);
	ray->delta_dist_x = fabs(TILE_SIZE / ray->dx);
	ray->delta_dist_y = fabs(TILE_SIZE / ray->dy);
	find_step_and_side_dist(data, ray);
	loop_for_wall_hit(data, ray, &hit);
	calculate_distance_to_wall(data, ray, ray_index, &hit);
}

void	render_walls(t_data *data)
{
	int		i;
	t_ray	*ray;
	t_walls	*wall;

	i = 0;
	wall = &data->wall;
	while (i < WIN_WIDTH)
	{
		ray = &data->rays[i];
		wall->corrected_dist = ray->distance * cos(ray->ray_angle
				- data->player.angle);
		if (wall->corrected_dist < 0.1)
			wall->corrected_dist = 0.1;
		wall->distance_to_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		wall->wall_height = (TILE_SIZE / wall->corrected_dist)
			* wall->distance_to_plane;
		wall->wall_start = (WIN_HEIGHT / 2) - (wall->wall_height / 2);
		wall->wall_end = (WIN_HEIGHT / 2) + (wall->wall_height / 2);
		draw_wall(data, i, wall->wall_start, wall->wall_end);
		i++;
	}
}
