#include "cub_3d.h"

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
	line =  get_next_line(fd);
	while(line && !search_map(line))
	{
		free(line);
		line =  get_next_line(fd);
	}
	data->map = malloc(sizeof(char *) * data->map_height);
	if(!data->map)
		return;
	while (line && search_map(line))
	{
		// printf("%s", line);
		data->map[i] = line;
		// free(line);
		line =  get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
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
	data->map_width = len_height(filename, data);
    add_map_line(data, filename);
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
    ft_bzero(data, sizeof(data));
    parse_cub(av[1], data);
	// printf("%d\n", data->map_width);
	int i = 0;
	while(data->map[i])
	{
		printf("%s", data->map[i]);
		i++;
	}
	// printf("textures.east[%s]\n", data->textures.east);
	// printf("textures.north[%s]\n", data->textures.north);
	// printf("textures.south{%s}\n", data->textures.south);
	// printf("textures.west{%s}\n", data->textures.west);
}
