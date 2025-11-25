#include "../include/cub_3d.h"

bool check_textures(char *line)
{
	if (!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2)
			|| !ft_strncmp("WE", line, 2) || !ft_strncmp("EA", line, 2)
			|| !ft_strncmp("F", line, 1)|| !ft_strncmp("C", line, 1))
			return(true);
	return (false);
}

char *skip_spacess(char *str )
{
	int	i;

	i = 0;
	if (!str)
		return(NULL);
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (str + i);
}
int duplicate_path(char *position, t_data *data)
{
	if (!ft_strncmp("NO", position, 2) && !data->flags.north)
	{
		data->flags.north = 1;
		return (0);
	}
	else if (!ft_strncmp("SO", position, 2) && !data->flags.south)
	{
		data->flags.south = 1;
		return (0);
	}
	else if (!ft_strncmp("WE", position, 2) && !data->flags.west)
	{
		data->flags.west = 1;
		return (0);
	}
	else if (!ft_strncmp("EA", position, 2) && !data->flags.east)
	{
		data->flags.east = 1;
		return (0);
	}
	else if (!ft_strncmp("F", position, 1) && !data->flags.floor)
	{
		data->flags.floor = 1;
		return (0);
	}
	else if (!ft_strncmp("C", position, 1) && !data->flags.ceiling)
	{
		data->flags.ceiling = 1;
		return (0);
	}
	return (1);
}

char *find_path(char *line, char *position, t_data *data)
{
	if(duplicate_path(position, data))
	{
		printf("Error\nDuplicate texture path\n");
		free_all_and_print_error(data, NULL);
	}
	if (!ft_strncmp(position, line, 2))
		line +=2;
	if (!ft_isspace(*line))
	{
		printf("Error\nInvalid texture path\n");
		free(line);
		free_all_and_print_error(data, NULL);
	}
	line = skip_spacess(line);
	strip_newline(line);
	return (line);
}

void pars_textures(char *line, t_data *data, int *offset)
{
	if(!line)
		return;
	line = skip_spacess(line);
	if(check_textures(line))
	{
		(*offset)++;
		if(!ft_strncmp("NO", line, 2))
			data->textures.north = ft_strdup(find_path(line, "NO", data));
		else if(!ft_strncmp("SO", line, 2))
			data->textures.south = ft_strdup(find_path(line, "SO", data));
		else if(!ft_strncmp("WE", line, 2))
			data->textures.west = ft_strdup(find_path(line, "WE", data));
		else if(!ft_strncmp("EA", line, 2))
			data->textures.east = ft_strdup(find_path(line, "EA", data));
		else if (!ft_strncmp("C", line, 1) && find_int(line))
			data->ceiling_color = parse_color_to_int(line, data);
		else if (!ft_strncmp("F", line, 1) && find_int(line))
			data->floor_color = parse_color_to_int(line, data);
	}
}

void define_textures(t_data *data, int fd, int *offset)
{
	char *line;

	line = get_next_line(fd);
	printf("Initial offset in define_textures: %d\n", *offset);
	while (line)
	{
		if (*offset <= 6)
		{
			pars_textures(line, data, offset);
			free(line);
		}
		else
			break;
		if(!line)
			break;
		
		line = get_next_line(fd);
	}
	free(line);
	if(*offset < 6 || !data->flags.north || !data->flags.south
		|| !data->flags.west || !data->flags.east
		|| !data->flags.floor || !data->flags.ceiling || *offset > 6)
	{
		printf("Error\nInvalid texture or color definition\n");
		free_all_and_print_error(data, NULL);
	}
	close(fd);
}

