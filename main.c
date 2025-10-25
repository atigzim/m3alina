#include "cub_3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	exit_map(char **map)
{
	write(1, "Error\n", 6);
	write(1, "map invalid\n", 13);
	free_map(map);
	exit(1);
}

int	len_height(char *path_file)
{
	int		fd;
	int		len;
	char	*r_l_map;

	fd = open(path_file, O_RDONLY);
	if (fd == -1)
		return (-1);
	len = 0;
	r_l_map = get_next_line(fd);
	while (r_l_map && r_l_map[0] == '1')
	{
		len++;
		free(r_l_map);
		r_l_map = get_next_line(fd);
	}
	free(r_l_map);
	return (len);
}

void	loop_map(char *r_l_line, int fd, char **map, t_data *data)
{
	while (r_l_line)
	{
		if (r_l_line[0] != '\n')
		{
			free(r_l_line);
			free(data);
			exit_map(map);
		}
		free(r_l_line);
		r_l_line = get_next_line(fd);
	}
}

char	**get_map(char *path_file, int len, t_data *data)
{
	int		fd;
	int		i;
	char	*r_l_line;
	char	**map;

	fd = open(path_file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < len)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	r_l_line = get_next_line(fd);
	loop_map(r_l_line, fd, map, data);
	close(fd);
	return (map);
}

void	check_dot_ber(char *path_file, t_data *data)
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
				write(1, "Only valid \".ber\" map files are allowed!\n", 42);
				exit(1);
			}
		}
		i++;
	}
	if (ft_strncmp(path_file + ft_strlen(path_file) - 4, ".ber", 4))
	{
		free(data);
		write(1, "Error\n", 6);
		write(1, "Only valid \".ber\" map files are allowed!\n", 42);
		exit(1);
	}
}

void parse_cub(char *filename, t_data *data)
{
    int fd;

    check_dot_ber(filename, data);
    fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
    // data->map = get_map()
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
}
