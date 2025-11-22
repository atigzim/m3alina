/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:05:47 by abhmidat          #+#    #+#             */
/*   Updated: 2025/11/19 15:33:17 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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