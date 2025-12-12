/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:34 by abhmidat          #+#    #+#             */
/*   Updated: 2025/12/11 23:17:44 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

static int	calculate_and_clamp_texture_x(t_ray *ray, t_image *texture)
{
	double	wall_x;
	int		tex_x;

	if (ray->is_vertical_hit == 1)
		wall_x = ray->ray_y / TILE_SIZE;
	else
		wall_x = ray->ray_x / TILE_SIZE;
	wall_x = wall_x - floor(wall_x);
	tex_x = (int)(wall_x * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	return (tex_x);
}

static int	init_wall_draw_params(t_data *data, int ray_index,
		double wall_top, double wall_bottom)
{
	t_image	*texture;
	int		tex_x;

	texture = texture_decide(data, &data->rays[ray_index]);
	data->wall.wall_height = (int)(wall_bottom - wall_top);
	data->wall.wall_start = (int)wall_top;
	data->wall.wall_end = (int)wall_bottom;
	if (data->wall.wall_start < 0)
		data->wall.wall_start = 0;
	if (data->wall.wall_end >= WIN_HEIGHT)
		data->wall.wall_end = WIN_HEIGHT;
	tex_x = calculate_and_clamp_texture_x(&data->rays[ray_index], texture);
	return (tex_x);
}

void	draw_wall(t_data *data, int ray_index,
		double wall_top, double wall_bottom)
{
	t_image	*texture;
	int		y;
	int		tex_x;
	int		tex_y;
	int		pixel_color;

	tex_x = init_wall_draw_params(data, ray_index, wall_top, wall_bottom);
	texture = texture_decide(data, &data->rays[ray_index]);
	y = data->wall.wall_start;
	while (y < data->wall.wall_end)
	{
		tex_y = (((y * 256 - WIN_HEIGHT * 128 + data->wall.wall_height * 128)
					* texture->height) / data->wall.wall_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		pixel_color = texture_get_pixel(texture, tex_x, tex_y);
		put_pixel_to_buffer(&data->buffer, ray_index, y, pixel_color);
		y++;
	}
}

void	put_pixel_to_buffer(t_image *buffer, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = buffer->pixel_data + (y * buffer->line_size
			+ x * (buffer->bpp / 8));
	*(unsigned int *)pixel = color;
}
