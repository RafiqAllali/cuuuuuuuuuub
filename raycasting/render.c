/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:33:28 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:39 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	draw_ceiling_floor(t_game *game)
{
	uint32_t	*pixels;
	int			ceiling_y;
	int			ceiling_x;
	int			floor_y;
	int			floor_x;

	pixels = (uint32_t *)game->img->pixels;
	ceiling_y = 0;
	while (ceiling_y < SCREEN_HEIGHT / 2)
	{
		ceiling_x = 0;
		while (ceiling_x < SCREEN_WIDTH)
		{
			pixels[ceiling_y * SCREEN_WIDTH + ceiling_x] = game->ceiling_color;
			ceiling_x++;
		}
		ceiling_y++;
	}
	floor_y = SCREEN_HEIGHT / 2;
	while (floor_y < SCREEN_HEIGHT)
	{
		floor_x = 0;
		while (floor_x < SCREEN_WIDTH)
		{
			pixels[floor_y * SCREEN_WIDTH + floor_x] = game->floor_color;
			floor_x++;
		}
		floor_y++;
	}
}

void	normalize_angle(double *angle)
{
	if (*angle < 0)
		*angle += PI2;
	if (*angle >= PI2)
		*angle -= PI2;
}

void	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cast_rays(game);
}
