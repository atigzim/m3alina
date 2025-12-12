/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 13:02:42 by abhmidat          #+#    #+#             */
/*   Updated: 2025/12/12 01:17:08 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int	texture_get_pixel(t_image *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->pixel_data + (y * tex->line_size + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	load_texture(t_data *data, t_image *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(
			data->mlx, path, &tex->width, &tex->height
			);
	if (!tex->img_ptr)
	{
		write(2, "Error\nFailed to load texture\n", 30);
		free_mlx(data);
		if(data)
			free_data(data);
		return (1);
	}
	tex->pixel_data = mlx_get_data_addr(
			tex->img_ptr, &tex->bpp, &tex->line_size, &tex->endian
			);
	if (!tex->pixel_data)
	{
		write(2, "Error\nFailed to get texture address\n", 37);
		mlx_destroy_image(data->mlx, tex->img_ptr);
		tex->img_ptr = NULL;
		free_mlx(data);
		if(data)
			free_data(data);
		return (1);
	}
	return (0);
}

static int	norm_set_textures(t_data *data)
{
	if (load_texture(data, &data->tex_no, data->textures.north))
	{
		if (data->tex_no.img_ptr)
			mlx_destroy_image(data->mlx, data->tex_no.img_ptr);
		return (1);
	}
	if (load_texture(data, &data->tex_so, data->textures.south))
	{
		if (data->tex_so.img_ptr)
			mlx_destroy_image(data->mlx, data->tex_so.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_no.img_ptr);
		return (1);
	}
	return (0);
}

int	set_textures(t_data *data)
{
	norm_set_textures(data);
	if (load_texture(data, &data->tex_we, data->textures.west))
	{
		if (data->tex_we.img_ptr)
			mlx_destroy_image(data->mlx, data->tex_we.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_so.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_no.img_ptr);
		return (1);
	}
	if (load_texture(data, &data->tex_ea, data->textures.east))
	{
		if (data->tex_ea.img_ptr)
			mlx_destroy_image(data->mlx, data->tex_ea.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_we.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_so.img_ptr);
		mlx_destroy_image(data->mlx, data->tex_no.img_ptr);
		return (1);
	}
	return (0);
}

t_image	*texture_decide(t_data *data, t_ray *ray)
{
	if (ray->is_vertical_hit == 1)
	{
		if (ray->ray_x > data->player.x)
			return (&data->tex_ea);
		else
			return (&data->tex_we);
	}
	else
	{
		if (ray->ray_y > data->player.y)
			return (&data->tex_so);
		else
			return (&data->tex_no);
	}
}
