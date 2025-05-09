/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:16:52 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:53:28 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	store_map_dimensions(t_map *map)
{
	int	y;
	int	max_width;
	int	current_width;

	y = 0;
	max_width = 0;
	while (y < map->height)
	{
		current_width = ft_strlen(map->grid[y]);
		if (current_width > max_width)
			max_width = current_width;
		y++;
	}
	map->width = max_width;
}

void	free_map_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}
