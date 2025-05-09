/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:46:08 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:54:04 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]) && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len--)
	{
		*ptr = (unsigned char)c;
		ptr++;
	}
	return (b);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		len;
	char	*str;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	str = (char *)ft_malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

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
