/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:33:28 by rallali           #+#    #+#             */
/*   Updated: 2025/05/10 04:05:53 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

static void	draw_ceiling(t_game *game, uint32_t *pixels)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixels[y * SCREEN_WIDTH + x] = game->ceiling_color;
			x++;
		}
		y++;
	}
}

static void	draw_floor(t_game *game, uint32_t *pixels)
{
	int	y;
	int	x;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			pixels[y * SCREEN_WIDTH + x] = game->floor_color;
			x++;
		}
		y++;
	}
}

void	draw_ceiling_floor(t_game *game)
{
	uint32_t	*pixels;

	pixels = (uint32_t *)game->img->pixels;
	draw_ceiling(game, pixels);
	draw_floor(game, pixels);
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
