#include "cub_3d.h"

char *padd_line(char *line, int len)
{
	int i;
	char *new_line;

	i = 0;
	new_line = malloc(len);
	while(i < len)
	{
		if(line)
			new_line[i] = line[i];
		else
			new_line[i] = 'A';
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
		{

			return(NULL);
		}
		new_map[i] = padd_line(data->map[i], data->map_width + 1);
		i++;
	}
	new_map[i] = NULL;
	return(new_map);
}

bool check_wall(t_data *data, int i, int j)
{
	if( i == 0 || j == 0 || i == data->map_height -1
			|| j == data->map_width -1 )
			return (true);
	return (false);

}
bool check_out(char **map, int i, int j)
{
	if( map[i][j - 1] == 'A' || map[i][j + 1] == 'A'
		|| map[i + 1][j] == 'A' || map[i - 1][j] == 'A')
		return (true);
	return (false);
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
			if(check_wall(data, i, j))
			{
				if(map[i][j] != '1' || map[i][j] != 'A')
				{
					//free_all;
					printf("error\nmap inavlid\n");
					exit(1);
				}
			}
			if (check_out(map, i, j))
			{
				//free_all;
				printf("error\nmap inavlid\n");
				exit(1);				
			}
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

    while (line && search_map(line))
    {
        data->map[i] = ft_strdup(line);
        strip_newline(data->map[i]);
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
	data->map_width = len_height(filename, data);
    add_map_line(data, filename);
	// map_valid(new_map(data), data);
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
	// int i = 0;
	// while(data->map[i])
	// {
	// 	printf("%s", data->map[i]);
	// 	i++;
	// }
	// printf("textures.east[%s]\n", data->textures.east);
	// printf("textures.north[%s]\n", data->textures.north);
	// printf("textures.south{%s}\n", data->textures.south);
	// printf("textures.west{%s}\n", data->textures.west);
}
