/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:11:10 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 22:48:52 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	cast_rays(t_game *game)
{
	int		x;
	double	camera_x;
	double	ray_angle;

	draw_ceiling_floor(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD * camera_x;
		normalize_angle(&ray_angle);
		cast_single_ray(game, x, ray_angle);
		x++;
	}
}

void	cast_single_ray(t_game *game, int x, double ray_angle)
{
	t_ray	ray;
	t_dda	dda;

	ray.angle = ray_angle;
	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);
	dda.map_x = (int)game->player.x;
	dda.map_y = (int)game->player.y;
	init_dda_params(&dda, &ray);
	setup_dda(game, &dda, &ray);
	perform_dda(game, &dda);
	render_wall(game, x, &ray, &dda);
}
