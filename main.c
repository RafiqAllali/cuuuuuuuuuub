/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:05:30 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:11 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

static int	process_line(char *line, t_config *config, int *map_started, int *i)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\n");
	free(line);
	if (*map_started && trimmed[0] == '\0')
	{
		free(trimmed);
		trimmed = ft_strdup(" ");
	}
	else if (trimmed[0] == '\0' || trimmed[0] == '#')
	{
		free(trimmed);
		return (0);
	}
	if (handle_textures(trimmed, config, map_started))
		return (free(trimmed), 0);
	if (handle_colors(trimmed, config, map_started))
		return (free(trimmed), 0);
	if (handle_map_line(trimmed, config, map_started, i))
		return (free(trimmed), 0);
	write(2, "Error: Invalid line in map file\n", 32);
	return (free(trimmed), 1);
}

void	read_map(int fd, t_config *config)
{
	char	*line;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, config, &map_started, &i))
			return ;
		line = get_next_line(fd);
	}
	config->map.height = i;
}

int	check_availaibility(t_config *config)
{
	if (!config->textures.north)
		return (1);
	if (!config->textures.south)
		return (1);
	if (!config->textures.east)
		return (1);
	if (!config->textures.west)
		return (1);
	return (0);
}

int	parsing(t_config *config, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	config->map.grid = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
	if (config->map.grid == NULL)
	{
		write(2, "Error: Memory allocation failed\n", 31);
		close(fd);
		return (1);
	}
	read_map(fd, config);
	if (check_availaibility(config) == 1 || check_colors_availability(config))
		return (write(2, "Error: invalid map\n", 19), 1);
	if (validate_configuration(config)
		|| validate_map_walls(&config->map)
		|| validate_player_position(&config->map))
	{
		write(2, "Error: Invalid configuration\n", 30);
		return (1);
	}
	store_map_dimensions(&config->map);
	return (close(fd), 0);
}

void	init_data(t_config *config)
{
	config->textures.north = NULL;
	config->textures.south = NULL;
	config->textures.west = NULL;
	config->textures.east = NULL;
	config->colors.floor[0] = -1;
	config->colors.floor[1] = -1;
	config->colors.floor[2] = -1;
	config->colors.floor[3] = -1;
	config->colors.ceiling[0] = -1;
	config->colors.ceiling[1] = -1;
	config->colors.ceiling[2] = -1;
	config->colors.ceiling[3] = -1;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->map.player_dir = 0;
	config->map.player_x = 0;
	config->map.player_y = 0;
	config->colors.floor_set = 0;
	config->colors.cell_set = 0;
}

int	main(int ac, char **av)
{
	t_config	config;

	if (ac != 2 || check_extension(av[1]) == 1)
	{
		write(2, "Error: Usage: ./cub3D <map.cub>\n", 32);
		return (1);
	}
	init_data(&config);
	if (parsing(&config, av[1]) == 1)
		return (1);
	game_loop(&config);
	free_map_grid(&config.map);
	free(config.textures.north);
	free(config.textures.south);
	free(config.textures.east);
	free(config.textures.west);
	return (0);
}
