/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:45:48 by atigzim           #+#    #+#             */
/*   Updated: 2025/12/12 01:12:04 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	pars_main(t_data *data, char *av)
{
	parse_cub(av, data);
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		free_data(data);
		exit(1);
	}
	if (set_textures(data))
	{
		write(2, "Error\nTexture loading failed\n", 30);
		exit(1);
	}
	data->window = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->window)
	{
		free_data(data);
		exit(1);
	}
	init_buffer(data);
	init_player(data);
	init_rays(data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}

bool	xpm_valid(char *path_file)
{
	int	len;

	len = ft_strlen(path_file);
	if (len < 4)
		return (false);
	if (ft_strncmp(path_file + (len - 4), ".xpm", 4))
	{
		return (false);
	}
	return (true);
}

void	parse_xpm(t_data *data)
{
	if (!xpm_valid(data->textures.east) || !xpm_valid(data->textures.west)
		|| !xpm_valid(data->textures.north) || !xpm_valid(data->textures.south))
	{
		printf("Error\nInvalid texture file extension (must be .xpm)\n");
		free_data(data);
		exit(1);
	}
}

void	parse_cub(char *filename, t_data *data)
{
	int	fd;
	int	offset;

	offset = 0;
	has_cub_extension(filename, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(printf("Error\nCannot open .cub file\n"), exit(1));
	define_textures(data, fd, &offset);
	parse_xpm(data);
	data->map_height = len_height(filename, data, &offset);
	add_map_line(data, filename);
	map_valid(new_map(data, fd), data);
	close(fd);
}
