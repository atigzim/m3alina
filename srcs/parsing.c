#include "../include/cub_3d.h"

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

int	len_height(char *filename, t_data *data, int *offset)
{
	int		len;
	char	*r_l_map;
	int fd;

	len = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_all_and_print_error(data, NULL, NULL);
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	r_l_map = get_next_line(fd);
	while(r_l_map && !search_map(r_l_map) && offset)
	{
		free(r_l_map);
		(*offset)--;
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

bool parse_color_textue(char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if(line[i] == ',')
			flag++;
		i++;
	}
	if (flag != 2)
		return (false);
	return (true);
}

int parse_color_to_int(char *line, t_data *data, char *original_line)
{
    int i ;

	i = 0;
	if (!parse_color_textue(line))
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    if (*line == 'C' || *line == 'F')
        line++;
    line = skip_spacess(line);
    data->f_c_color.r = ft_atoi(line);
    if (data->f_c_color.r < 0 || data->f_c_color.r > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    while (line[i] && line[i] != ',')
        i++;
    i++; 
    data->f_c_color.g = ft_atoi(line + i);
    if (data->f_c_color.g < 0 || data->f_c_color.g > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    while (line[i] && line[i] != ',')
        i++;
    i++;
    data->f_c_color.b = ft_atoi(line + i);
    if (data->f_c_color.b < 0 || data->f_c_color.b > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    return (data->f_c_color.r << 16 | data->f_c_color.g << 8 | data->f_c_color.b);
}


