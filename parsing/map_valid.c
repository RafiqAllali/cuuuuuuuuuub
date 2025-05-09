/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:06:35 by rallali           #+#    #+#             */
/*   Updated: 2025/05/10 04:11:20 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

static int	check_border_cell(t_map *map, int y, int x, int len)
{
	if ((y == 0 || y == map->height - 1 || x == 0 || x == len - 1)
		&& (map->grid[y][x] != '1' && !is_space_or_tab(map->grid[y][x])))
	{
		write(2, "Error: Invalid map border\n", 27);
		return (1);
	}
	return (0);
}

int	validate_map_walls(t_map *map)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		len = ft_strlen(map->grid[y]);
		while (x < len)
		{
			if (check_border_cell(map, y, x, len))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void	process_player_cell(t_map *map, int y, int x, int *player_count)
{
	if (ft_strchr("NSEW", map->grid[y][x]))
	{
		(*player_count)++;
		map->player_dir = map->grid[y][x];
		map->player_x = x;
		map->player_y = y;
		map->grid[y][x] = '0';
	}
}

int	validate_player_position(t_map *map)
{
	int	y;
	int	x;
	int	player_count;

	y = 0;
	player_count = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			process_player_cell(map, y, x, &player_count);
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		write(2, "Error: Map must contain exactly one player\n", 43);
		return (1);
	}
	return (0);
}

int	process_line(char *line, t_config *config, int *map_started, int *i)
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
