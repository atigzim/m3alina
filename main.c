#include "cub_3d.h"

char *padd_line(char *line, int len)
{
	int i;
	char *new_line;

	i = 0;
	new_line = malloc(len);
	ft_bzero(new_line, len);
	while(i < len)
	{
		if(i < (int)ft_strlen(line) && line[i])
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return(new_line);
}

char **new_map(t_data *data)
{
	char **new_map;
	int i;

	i = 0;
	new_map = malloc(sizeof(char *) * (data->map_height + 1));
	if(!new_map)
		return(NULL);
	while(data->map[i])
	{
		new_map[i] = malloc(sizeof(char) * (data->map_width + 1));
		if(!new_map[i])
			return(NULL);
		ft_bzero(new_map[i], sizeof(char) * (data->map_width));
		new_map[i] = padd_line(data->map[i], data->map_width);
		i++;
	}
	new_map[i] = NULL;
	return(new_map);
}

bool check_wall(t_data *data, int lne, int i, int j)
{
	if( i == 0 || j == 0 || i == data->map_height
			|| j == lne - 1 )
			return (true);
	return (false);

}
bool check_out(char **map, int i, int j)
{
	if(map[i][j] == '0' && (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
		|| map[i + 1][j] == ' ' || map[i - 1][j] == ' '))
		return (true);
	return (false);
}
void check_valid_character(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
	{
		// free_all
		printf("error\ninvalid character in map\n");
		exit(1);
	}
}

void map_valid(char **map, t_data *data)
{
	int i;
	int j;

	i = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(check_wall(data, ft_strlen(map[i]), i, j))
				if(map[i][j] != '1' && !ft_isspace(map[i][j]))
					free_all_and_print_error(data, map);
			if (check_out(map, i, j))
				free_all_and_print_error(data, map);
			if(map[i][j] != ' ')
				check_valid_character(map[i][j]);
			j++;
		}
		i++;
	}
}

bool search_map(char *line)
{
	int i ;

	i = 0;
	if(!line)
		return(false);
	if(check_textures(line))
		return(false);
	while (line[i])
	{
		if(line[i] == '1' || line[i] == '0')
			return(true);
		i++;
	}
	return(false);
}

void add_map_line(t_data *data, char *filename)
{
    int fd;
    char *line;
    int i = 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open .cub file\n");
        exit(1);
    }

    line = get_next_line(fd);
    while (line && !search_map(line))
    {
        free(line);
        line = get_next_line(fd);
    }

    data->map = malloc(sizeof(char *) * (data->map_height + 1));
    if (!data->map)
        return;
    while (line && i < data->map_height && search_map(line))
    {
        data->map[i] = ft_strdup(line);
        data->map[i] = strip_newline(data->map[i]);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    data->map[i] = NULL;
    close(fd);
}



void parse_cub(char *filename, t_data *data)
{
    int fd;

    has_cub_extension(filename, data);
    fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		//free_all
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	define_textures(data, fd);
	data->map_height = len_height(filename, data);
    add_map_line(data, filename);
	map_valid(new_map(data), data);
	close(fd);
}

int main(int ac, char *av[])
{
    t_data  *data;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }
	data = malloc(sizeof(t_data)); 
	if(!data)
		return(1);
	ft_bzero(data, sizeof(t_data));
    parse_cub(av[1], data);
	// printf("%d\n", data->map_width);
	// printf("textures.east[%s]\n", data->textures.east);
	// printf("textures.north[%s]\n", data->textures.north);
	// printf("textures.south{%s}\n", data->textures.south);
	// printf("textures.west{%s}\n", data->textures.west);
}
