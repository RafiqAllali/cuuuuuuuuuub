/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:11:10 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 23:02:29 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	render_wall(t_game *game, int x, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		ray->true_dist = (dda->map_x - game->player.x
				+ (1 - dda->step_x) / 2) / ray->dir_x;
	else
		ray->true_dist = (dda->map_y - game->player.y
				+ (1 - dda->step_y) / 2) / ray->dir_y;
	ray->perp_wall_dist = ray->true_dist * cos(ray->angle - game->player.angle);
	calculate_wall_drawing(game, x, ray, dda);
}

void	calculate_wall_drawing(t_game *game, int x, t_ray *ray, t_dda *dda)
{
	t_wall	wall;

	wall.line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	wall.draw_start = -wall.line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall.draw_start < 0)
		wall.draw_start = 0;
	wall.draw_end = wall.line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall.draw_end >= SCREEN_HEIGHT)
		wall.draw_end = SCREEN_HEIGHT - 1;
	select_texture_and_draw(game, x, ray, &wall, dda->side);
}
