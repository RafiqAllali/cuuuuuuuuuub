/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:08:25 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:53:21 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

int	validate_configuration(t_config *config)
{
	if (config->textures.north && access(config->textures.north, R_OK) == -1)
		return (write(2, "Error: Cannot access north texture\n", 34), 1);
	if (config->textures.south && access(config->textures.south, R_OK) == -1)
		return (write(2, "Error: Cannot access south texture\n", 34), 1);
	if (config->textures.west && access(config->textures.west, R_OK) == -1)
		return (write(2, "Error: Cannot access west texture\n", 33), 1);
	if (config->textures.east && access(config->textures.east, R_OK) == -1)
		return (write(2, "Error: Cannot access east texture\n", 33), 1);
	if (config->colors.floor[0] == -1
		|| config->colors.floor[1] == -1
		|| config->colors.floor[2] == -1)
		return (write(2, "Error: Floor color not set\n", 27), 1);
	if (config->colors.ceiling[0] == -1
		|| config->colors.ceiling[1] == -1
		|| config->colors.ceiling[2] == -1)
		return (write(2, "Error: Ceiling color not set\n", 29), 1);
	return (0);
}
