/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:21:52 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:23 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	key_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	handle_movement(game);
	handle_rotation(game);
}

void	handle_movement(t_game *game)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		move_x += cos(game->player.angle) * MOVE_SPEED;
		move_y += sin(game->player.angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		move_x -= cos(game->player.angle) * MOVE_SPEED;
		move_y -= sin(game->player.angle) * MOVE_SPEED;
	}
	handle_strafing(game, &move_x, &move_y);
}

void	handle_rotation(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= ROT_SPEED;
		if (game->player.angle < 0)
			game->player.angle += PI2;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += ROT_SPEED;
		if (game->player.angle >= PI2)
			game->player.angle -= PI2;
	}
}
