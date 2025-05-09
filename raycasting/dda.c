/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:11:10 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 22:43:21 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	init_dda_params(t_dda *dda, t_ray *ray)
{
	dda->delta_dist_x = fabs(1 / ray->dir_x);
	dda->delta_dist_y = fabs(1 / ray->dir_y);
	dda->hit = 0;
}

void	setup_dda(t_game *game, t_dda *dda, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player.x - dda->map_x) * fabs(1 / ray->dir_x);
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.x)
			* fabs(1 / ray->dir_x);
	}
	if (ray->dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player.y - dda->map_y) * fabs(1 / ray->dir_y);
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.y)
			* fabs(1 / ray->dir_y);
	}
}

void	perform_dda(t_game *game, t_dda *dda)
{
	while (!(dda->hit))
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_y < 0 || dda->map_y >= game->map.height
			|| dda->map_x < 0 || dda->map_x >= game->map.width
			|| game->map.grid[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
}
