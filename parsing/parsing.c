#include "../cub_3d.h"

char *strip_newline(char *line)
{
    size_t i = 0;
    while (line[i])
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            return line;
        }
        i++;
    }
	return line;
}

int	len_height(char *filename, t_data *data)
{
	int		len;
	char	*r_l_map;
	int fd;

	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		//free_all
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	r_l_map = get_next_line(fd);
	while(r_l_map && !search_map(r_l_map))
	{
		free(r_l_map);
		r_l_map = get_next_line(fd);
	}
	while (r_l_map && search_map(r_l_map))
	{
		len++;
		if ((int)ft_strlen(r_l_map) -1 > data->map_width)
			data->map_width = ft_strlen(r_l_map) -1;
		free(r_l_map);
		r_l_map = get_next_line(fd);
	}
	free(r_l_map);
	close(fd);
	return (len);
}

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
				free(data);
				write(1, "Error\n", 6);
				write(1, "Only valid \".cub\" map files are allowed!\n", 42);
				exit(1);
			}
		}
		i++;
	}
	if (ft_strncmp(path_file + ft_strlen(path_file) - 4, ".cub", 4))
	{
		free(data);
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
		if (!ft_strncmp("C", line, 1) || !ft_strncmp("F", line, 1))
		{
			line++;
			line = skip_spacess(line);
		}
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
		else
		{
			printf("errrrrrr\n");
			exit(1);
		}
	}
	return(NULL);
}
