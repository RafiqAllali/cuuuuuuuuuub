/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:26:06 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:26 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	handle_strafing(t_game *game, float *move_x, float *move_y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*move_x += cos(game->player.angle - PI / 2) * MOVE_SPEED;
		*move_y += sin(game->player.angle - PI / 2) * MOVE_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*move_x += cos(game->player.angle + PI / 2) * MOVE_SPEED;
		*move_y += sin(game->player.angle + PI / 2) * MOVE_SPEED;
	}
	if (*move_x != 0 || *move_y != 0)
		apply_movement(game, *move_x, *move_y);
}

void	apply_movement(t_game *game, float move_x, float move_y)
{
	float	new_x;
	float	new_y;
	float	buffer;

	new_x = game->player.x + move_x;
	new_y = game->player.y + move_y;
	buffer = 0.2;
	if ((int)new_x >= 0 && (int)new_x < game->map.width
		&& (int)game->player.y >= 0 && (int)game->player.y < game->map.height
		&& game->map.grid[(int)game->player.y][(int)new_x] != '1'
		&& game->map.grid[(int)(game->player.y - buffer)][(int)new_x] != '1'
		&& game->map.grid[(int)(game->player.y + buffer)][(int)new_x] != '1')
		game->player.x = new_x;
	check_y_collision(game, new_y, buffer);
}

void	check_y_collision(t_game *game, float new_y, float buffer)
{
	if ((int)game->player.x >= 0 && (int)game->player.x < game->map.width
		&& (int)new_y >= 0 && (int)new_y < game->map.height
		&& game->map.grid[(int)new_y][(int)game->player.x] != '1'
		&& game->map.grid[(int)new_y][(int)(game->player.x - buffer)] != '1'
		&& game->map.grid[(int)new_y][(int)(game->player.x + buffer)] != '1')
		game->player.y = new_y;
}
