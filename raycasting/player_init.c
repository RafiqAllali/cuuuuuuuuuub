/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:28:49 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:30 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	set_player_angle(t_game *game, t_config *config)
{
	game->player.angle = 0;
	if (config->map.player_dir == 'N')
		game->player.angle = 270 * DEG_TO_RAD;
	else if (config->map.player_dir == 'S')
		game->player.angle = 90 * DEG_TO_RAD;
	else if (config->map.player_dir == 'E')
		game->player.angle = 0;
	else if (config->map.player_dir == 'W')
		game->player.angle = 180 * DEG_TO_RAD;
}

bool	init_game(t_game *game, t_config *config)
{
	set_player_angle(game, config);
	game->player.x = config->map.player_x + 0.5;
	game->player.y = config->map.player_y + 0.5;
	game->map = config->map;
	return (init_colors_and_window(game, config));
}

bool	init_colors_and_window(t_game *game, t_config *config)
{
	game->ceiling_color = (config->colors.ceiling[0] << 16)
		| (config->colors.ceiling[1] << 8)
		| (config->colors.ceiling[2])
		| (255 << 24);
	game->floor_color = (config->colors.floor[0] << 16)
		| (config->colors.floor[1] << 8)
		| (config->colors.floor[2])
		| (255 << 24);
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", false);
	if (!game->mlx)
		return (false);
	return (init_textures_and_image(game, config));
}
