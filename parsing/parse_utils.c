#include "../cub_3d.h"

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

char *find_path(char *line, char *position)
{
	if (!ft_strncmp(position, line, 2))
		line +=2;
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
			data->textures.north = ft_strdup(find_path(line, "NO"));
		else if(!ft_strncmp("SO", line, 2))
			data->textures.south = ft_strdup(find_path(line, "SO"));
		else if(!ft_strncmp("WE", line, 2))
			data->textures.west = ft_strdup(find_path(line, "WE"));
		else if(!ft_strncmp("EA", line, 2))
			data->textures.east = ft_strdup(find_path(line, "EA"));
		else if (!ft_strncmp("C", line, 1))
			data->ceiling = ft_strdup(find_int(line)); 
		else if (!ft_strncmp("F", line, 1))
			data->floor = ft_strdup(find_int(line)); 
	}
}

void define_textures(t_data *data, int fd)
{
	char *line;
	int offset;

	offset = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (offset <= 6)
		{
			pars_textures(line, data, &offset);
			free(line);
		}
		else
			break;
		line = get_next_line(fd);
	}
	free(line);
}
