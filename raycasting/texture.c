/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 23:34:31 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 23:34:33 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	select_texture_and_draw(t_game *game, int x, \
t_ray *ray, t_wall *wall, int side)
{
	if (side == 0)
	{
		if (ray->dir_x > 0)
			wall->tex_num = EAST;
		else
			wall->tex_num = WEST;
	}
	else
	{
		if (ray->dir_y > 0)
			wall->tex_num = SOUTH;
		else
			wall->tex_num = NORTH;
	}
	if (side == 0)
		wall->wall_x = game->player.y + ray->true_dist * ray->dir_y;
	else
		wall->wall_x = game->player.x + ray->true_dist * ray->dir_x;
	wall->wall_x -= floor(wall->wall_x);
	draw_textured_line(game, x, wall, ray, side);
}
