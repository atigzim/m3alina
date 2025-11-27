#include "../include/cub_3d.h"

void free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->map)
		free_map(data->map);
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.west)
		free(data->textures.west);
	if (data->textures.east)
		free(data->textures.east);
	free(data);
}

void free_map(char **map)
{
	int i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}
void free_all_and_print_error(t_data *data, char **map, char *line)
{
	if(line)
		free(line);
	if (map)
		free_map(map);
	if(data)
		free_data(data);
    exit(1);
}