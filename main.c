#include "cub_3d.h"

// void	free_map(char **map)
// {
// 	int	i;

// 	if (!map)
// 		return ;
// 	i = 0;
// 	while (map[i])
// 	{
// 		free(map[i]);
// 		map[i] = NULL;
// 		i++;
// 	}
// 	free(map);
// 	map = NULL;
// }

// void	exit_map(char **map)
// {
// 	write(1, "Error\n", 6);
// 	write(1, "map invalid\n", 13);
// 	free_map(map);
// 	exit(1);
// }

int	len_height(int fd)
{
	int		len;
	char	*r_l_map;

	len = 0;
	r_l_map = get_next_line(fd);
	while (r_l_map && r_l_map[0] == '1')
	{
		len++;
		// free(r_l_map);
		r_l_map = get_next_line(fd);
	}
	// free(r_l_map);
	return (len);
}

// void	loop_map(char *r_l_line, int fd, char **map, t_data *mp)
// {
// 	while (r_l_line)
// 	{
// 		if (r_l_line[0] != '\0')
// 		{
// 			free(r_l_line);
// 			free(mp);
// 			exit_map(map);
// 		}
// 		free(r_l_line);
// 		r_l_line = get_next_line(fd);
// 	}
// }

// char	**get_map(int fd, int len, t_data *data)
// {	
// 	int		i;
// 	char	*r_l_line;
// 	char	**map;

// 	map = malloc(sizeof(char *) * (len + 1));
// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		map[i] = get_next_line(fd);
// 		i++;
// 	}
// 	map[i] = NULL;
// 	r_l_line = get_next_line(fd);
// 	loop_map(r_l_line, fd, map, data);
// 	close(fd);
// 	return (map);
// }

void	has_cub_extension(char *path_file, t_data *data)
{
	int	i;

	i = 0;
	while (path_file[i])
	{
		if (path_file[i] == '/' || ft_strlen(path_file) <= 4)
		{
			if (ft_strlen(&path_file[i + 1]) <= 4
				|| ft_strlen(path_file) <= 4)
			{
				// free(data);
				write(1, "Error\n", 6);
				write(1, "Only valid \".cub\" map files are allowed!\n", 42);
				exit(1);
			}
		}
		i++;
	}
	if (ft_strncmp(path_file + ft_strlen(path_file) - 4, ".cub", 4))
	{
		// free(data);
		write(1, "Error\n", 6);
		write(1, "Only valid \".cub\" map files are allowed!\n", 42);
		exit(1);
	}

}

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

char *find_int(char *line)
{
	int i;

	i = 0;
	if (!line)
		return(NULL);
	while (*line && *line != '\n')
	{
		if (ft_isdigit(*line))
		{
			while(line[i])
			{
				if(!ft_isdigit(line[i]) && !ft_isspace(line[i]) && line[i] != ',')
				{
					printf("errrrrrr\n");
					exit(1);
				}
				i++;
			}
			return(line);
		}
		line++;
	}
	return(NULL);
} 

bool check_textures(char *line)
{
	if (!ft_strncmp("NO", line, 2) && !ft_strncmp("SO", line, 2)
			&& !ft_strncmp("WE", line, 2) && !ft_strncmp("EA", line, 2)
			&& !ft_strncmp("F", line, 1)&& !ft_strncmp("C", line, 1))
			return(false);
	return (true);
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
	if (ft_strncmp(position, line, 2))
		line+=2;
	line = skip_spacess(line);
	return (line);
}

void pars_textures(char *line, t_data *data)
{
	int i;

	i = 0;
	if(!line)
		return;
	line = skip_spacess(line);
	if(check_textures(line))
	{
		i++;
		if(!ft_strncmp("NO", line, 2))
		{
			data->textures.north = ft_strdup(find_path(line, "NO"));
		}
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

void define_textures(t_data *data, int fd, int *offset)
{
	char *line;
	int i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (*offset < 6)
		{
			pars_textures(line, data);
			(*offset)++;
			// free(line);
		}
		else
			break;
		line = get_next_line(fd);
	}
}

void parse_cub(char *filename, t_data *data)
{
    int fd;
	int offset;

	offset = 0;
    has_cub_extension(filename, data);
    fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		//free_all
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	define_textures(data, fd, &offset);
	data->map_width = len_height(fd);
    data->map =
}

int main(int ac, char *av[])
{
    t_data  *data;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }
    data = malloc(sizeof(data)); 
    if(!data)
        return(1);
    ft_bzero(data, sizeof(data));
    parse_cub(av[1], data);
	// printf("textures.east[%s]\n", data->textures.east);
	// printf("textures.north[%s]\n", data->textures.north);
	// printf("textures.south{%s}\n", data->textures.south);
	// printf("textures.west{%s}\n", data->textures.west);
}
