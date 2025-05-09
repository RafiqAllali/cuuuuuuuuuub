/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:14:46 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:19 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

void	game_loop(t_config *config)
{
	t_game	game;

	if (!init_game(&game, config))
		return ;
	setup_and_run_game(&game);
}

void	setup_and_run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, &render_frame, game);
	mlx_loop_hook(game->mlx, &key_handler, game);
	mlx_loop(game->mlx);
	cleanup_game(game);
}

void	cleanup_game(t_game *game)
{
	int	i;

	mlx_delete_image(game->mlx, game->img);
	i = 0;
	while (i < 4)
	{
		mlx_delete_texture(game->textures[i]);
		i++;
	}
	mlx_terminate(game->mlx);
}
