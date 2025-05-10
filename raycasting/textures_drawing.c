/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_drawing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by rallali           #+#    #+#             */
/*   Updated: 2025/05/10 04:04:11 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	draw_textured_line(t_game *game, int x, t_wall *wall, t_ray *ray)
{
	int	side;

	side = wall->side;
	wall->tex_width = game->textures[wall->tex_num]->width;
	wall->tex_height = game->textures[wall->tex_num]->height;
	wall->tex_x = (int)(wall->wall_x * wall->tex_width);
	if ((side == 0 && ray->dir_x > 0) || (side == 1 && ray->dir_y < 0))
		wall->tex_x = wall->tex_width - wall->tex_x - 1;
	if (wall->tex_x < 0)
		wall->tex_x = 0;
	if (wall->tex_x >= wall->tex_width)
		wall->tex_x = wall->tex_width - 1;
	draw_vertical_line(game, x, wall);
}

static void	init_vertical_line(t_game *game, t_wall *wall,
			t_vertical_line *vline)
{
	vline->pixels = (uint32_t *)game->img->pixels;
	vline->step = (double)wall->tex_height / wall->line_height;
	vline->tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2
			+ wall->line_height / 2) * vline->step;
	vline->y = wall->draw_start;
}

static void	process_pixel(t_game *game, t_wall *wall,
			int tex_y, uint32_t *color)
{
	int		pixel_index;
	uint8_t	*pixel;

	pixel_index = (tex_y * wall->tex_width + wall->tex_x) * 4;
	if (pixel_index < 0
		|| pixel_index >= (wall->tex_width * wall->tex_height * 4))
		pixel_index = 0;
	pixel = &game->textures[wall->tex_num]->pixels[pixel_index];
	*color = (pixel[3] << 24) | (pixel[2] << 16)
		| (pixel[1] << 8) | pixel[0];
}

void	draw_vertical_line(t_game *game, int x, t_wall *wall)
{
	t_vertical_line	vline;

	init_vertical_line(game, wall, &vline);
	while (vline.y < wall->draw_end)
	{
		vline.tex_y = (int)vline.tex_pos % wall->tex_height;
		if (vline.tex_y < 0)
			vline.tex_y = 0;
		if (vline.tex_y >= wall->tex_height)
			vline.tex_y = wall->tex_height - 1;
		vline.tex_pos += vline.step;
		process_pixel(game, wall, vline.tex_y, &vline.color);
		vline.pixels[vline.y * SCREEN_WIDTH + x] = vline.color;
		vline.y++;
	}
}
