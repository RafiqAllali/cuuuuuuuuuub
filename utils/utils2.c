/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 04:06:35 by rallali           #+#    #+#             */
/*   Updated: 2025/05/10 04:06:58 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

int	check_extension(const char *filename)
{
	size_t	len;

	if (!filename)
		return (1);
	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	if (access(filename, F_OK) != 0)
		return (1);
	return (0);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "Error: Memory allocation failed\n", 31);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

void	error_exit(char *message, t_map *map)
{
	if (message)
		write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	if (map)
		exit(EXIT_FAILURE);
}
