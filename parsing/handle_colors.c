/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:06:35 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:53:24 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

static int	count_commas(char *line)
{
	int	commas;

	commas = 0;
	while (*line)
	{
		if (*line == ',')
			commas++;
		line++;
	}
	return (commas);
}

static void	process_color(char **rgb_values, int color[3], int *color_set)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (i < 3)
	{
		trimmed = ft_strtrim(rgb_values[i], " \t\n\r");
		color[i] = ft_atoi(trimmed);
		free(trimmed);
		free(rgb_values[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			write(2, "Error: Color values must be 0-255\n", 34);
			color[0] = -1;
			return ;
		}
		i++;
	}
	free(rgb_values);
	if (color[0] != -1)
		(*color_set)++;
}

static void	validate_rgb_values(char **rgb_values, int color[3], int *color_set)
{
	int	count;

	count = 0;
	while (rgb_values[count])
		count++;
	if (count != 3)
	{
		while (count--)
			free(rgb_values[count]);
		free(rgb_values);
		write(2, "Error: Color needs 3 values\n", 28);
		return ;
	}
	process_color(rgb_values, color, color_set);
}

void	parse_color(char *line, int color[3], int *color_set)
{
	char	**rgb_values;

	if (*color_set > 0)
	{
		write(2, "Error: Duplicate color definition\n", 33);
		return ;
	}
	while (*line == ' ')
		line++;
	if (count_commas(line) != 2)
	{
		write(2, "Error: Incorrect comma count\n", 29);
		return ;
	}
	rgb_values = ft_split(line, ',');
	if (!rgb_values)
	{
		write(2, "Error: Invalid color format\n", 28);
		return ;
	}
	validate_rgb_values(rgb_values, color, color_set);
}

int	check_colors_availability(t_config *config)
{
	return (config->colors.floor_set > 1 || config->colors.cell_set > 1);
}
