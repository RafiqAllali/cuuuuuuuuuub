/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:11:10 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:15 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	setup_dda(t_game *game, double *side_dist_x, double *side_dist_y,
			int *step_x, int *step_y, double ray_dir_x, double ray_dir_y,
			int map_x, int map_y)
{
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_dist_x = (game->player.x - map_x) * fabs(1 / ray_dir_x);
	}
	else
	{
		*step_x = 1;
		*side_dist_x = (map_x + 1.0 - game->player.x) * fabs(1 / ray_dir_x);
	}
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_dist_y = (game->player.y - map_y) * fabs(1 / ray_dir_y);
	}
	else
	{
		*step_y = 1;
		*side_dist_y = (map_y + 1.0 - game->player.y) * fabs(1 / ray_dir_y);
	}
}

void	perform_dda(t_game *game, int *hit, int *side, int *map_x, int *map_y,
			double *side_dist_x, double *side_dist_y,
			double delta_dist_x, double delta_dist_y,
			int step_x, int step_y)
{
	while (!(*hit))
	{
		if (*side_dist_x < *side_dist_y)
		{
			*side_dist_x += delta_dist_x;
			*map_x += step_x;
			*side = 0;
		}
		else
		{
			*side_dist_y += delta_dist_y;
			*map_y += step_y;
			*side = 1;
		}
		if (*map_y < 0 || *map_y >= game->map.height
			|| *map_x < 0 || *map_x >= game->map.width
			|| game->map.grid[*map_y][*map_x] == '1')
			*hit = 1;
	}
}
