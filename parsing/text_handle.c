/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:45:12 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:53:55 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

int	handle_colors(char *line, t_config *config, int *map_started)
{
	if (*map_started == 0 && ft_strncmp(line, "F ", 2) == 0)
	{
		parse_color(line + 2, config->colors.floor, &config->colors.floor_set);
		return (1);
	}
	else if (*map_started == 0 && ft_strncmp(line, "C ", 2) == 0)
	{
		parse_color(line + 2, config->colors.ceiling, &config->colors.cell_set);
		return (1);
	}
	return (0);
}

int	handle_map_line(char *line, t_config *config, int *map_started, int *i)
{
	if (ft_strchr("10NSEW ", line[0]))
	{
		*map_started = 1;
		if (*i >= MAX_MAP_HEIGHT)
		{
			write(2, "Error: Map exceeds max height\n", 30);
			return (0);
		}
		config->map.grid[*i] = ft_strdup(line);
		(*i)++;
		return (1);
	}
	return (0);
}

int	handle_textures(char *line, t_config *config, int *map_started)
{
	if (*map_started)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0 && !config->textures.north)
	{
		config->textures.north = ft_strdup(line + 3);
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0 && !config->textures.south)
	{
		config->textures.south = ft_strdup(line + 3);
		return (1);
	}
	if (ft_strncmp(line, "WE ", 3) == 0 && !config->textures.west)
	{
		config->textures.west = ft_strdup(line + 3);
		return (1);
	}
	if (ft_strncmp(line, "EA ", 3) == 0 && !config->textures.east)
	{
		config->textures.east = ft_strdup(line + 3);
		return (1);
	}
	return (0);
}
