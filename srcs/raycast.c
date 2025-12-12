/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:51:48 by atigzim           #+#    #+#             */
/*   Updated: 2025/12/11 19:13:20 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	grid_lines(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (x % TILE_SIZE == 0 || y % TILE_SIZE == 0)
				my_mlx_pixel_put(&data->buffer, x, y, 0xFFFFFF);
			if (x == (int)data->player.x && y == (int)data->player.y)
				draw_block(&data->buffer, x - 2, y - 2, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	draw_block(t_image *img, int x, int y, int cool)
{
	int	i;
	int	j;

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

void	draw_c_f(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		y = 0;
		while (y < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				my_mlx_pixel_put(&data->buffer, y, i, data->ceiling_color);
			else
				my_mlx_pixel_put(&data->buffer, y, i, data->floor_color);
			y++;
		}
		i++;
	}
}

void	draw_all(t_data *data)
{
	int	i;
	int	y;

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
	draw_c_f(data);
	cast_all_rays(data);
	render_walls(data);
}

void	cast_all_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		data->rays[i].ray_angle = data->player.angle
			- (FOV / 2) + (i * (FOV / (double)WIN_WIDTH));
		cast_one_ray(data, i);
		i++;
	}
}
