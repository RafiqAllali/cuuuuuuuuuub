/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:36:19 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 22:54:57 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

bool	init_textures_and_image(t_game *game, t_config *config)
{
	if (!load_textures(game, config))
		return (false);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img)
		return (false);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (false);
	return (true);
}

bool	load_textures(t_game *game, t_config *config)
{
	mlx_texture_t	*north_tex;
	mlx_texture_t	*south_tex;
	mlx_texture_t	*east_tex;
	mlx_texture_t	*west_tex;

	north_tex = mlx_load_png(config->textures.north);
	south_tex = mlx_load_png(config->textures.south);
	east_tex = mlx_load_png(config->textures.east);
	west_tex = mlx_load_png(config->textures.west);
	if (!north_tex || !south_tex || !east_tex || !west_tex)
		return (false);
	game->textures[NORTH] = north_tex;
	game->textures[SOUTH] = south_tex;
	game->textures[EAST] = east_tex;
	game->textures[WEST] = west_tex;
	return (true);
}
