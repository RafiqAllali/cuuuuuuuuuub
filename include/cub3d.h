/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rallali <rallali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:05:56 by rallali           #+#    #+#             */
/*   Updated: 2025/05/09 21:52:43 by rallali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "/Users/rallali/Desktop/cuuuuu/MLX42/include/MLX42/MLX42.h"

// Constants for raycasting and rendering
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEXTURE_SIZE 64
# define FOV 66.0
# define PI 3.14159265359
# define PI2 6.28318530718
# define DEG_TO_RAD 0.01745329251
# define RAD_TO_DEG 57.2957795131
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MAX_MAP_HEIGHT 100
# define BUFFER_SIZE 1024

// Texture indices
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// Colors
typedef struct s_colors
{
	int	floor[4];
	int	ceiling[4];
	int	floor_set;
	int	cell_set;
}	t_colors;

// Textures
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

// Map information
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_map;

// Configuration
typedef struct s_config
{
	t_textures	textures;
	t_colors	colors;
	t_map		map;
}	t_config;

// Player
typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}	t_player;

// Game state
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	t_player		player;
	t_map			map;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
}	t_game;

// get_next_line functions
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

// Parsing functions
int		parsing(t_config *config, char *filename);
void	init_data(t_config *config);
int		check_extension(const char *filename);
void	read_map(int fd, t_config *config);
int		check_availaibility(t_config *config);
int		check_colors_availability(t_config *config);

// Map validation
int		validate_configuration(t_config *config);
int		validate_map_walls(t_map *map);
int		validate_player_position(t_map *map);
void	store_map_dimensions(t_map *map);
void	free_map_grid(t_map *map);

// Handlers
int		handle_textures(char *line, t_config *config, int *map_started);
int		handle_colors(char *line, t_config *config, int *map_started);
int		handle_map_line(char *line, t_config *config, int *map_started, int *i);
void	parse_color(char *line, int color[3], int *color_set);

// Utils
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *s1);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(char *s, char c);
void	*ft_malloc(size_t size);
int		is_space_or_tab(char c);
int		is_wall_or_walkable(char c);

// Raycasting functions
void	game_loop(t_config *config);
bool	init_game(t_game *game, t_config *config);
bool	init_colors_and_window(t_game *game, t_config *config);
bool	init_textures_and_image(t_game *game, t_config *config);
bool	load_textures(t_game *game, t_config *config);
void	set_player_angle(t_game *game, t_config *config);

// Player movement and input
void	key_handler(void *param);
void	handle_movement(t_game *game);
void	handle_strafing(t_game *game, float *move_x, float *move_y);
void	apply_movement(t_game *game, float move_x, float move_y);
void	check_y_collision(t_game *game, float new_y, float buffer);
void	handle_rotation(t_game *game);

// Rendering functions
void	render_frame(void *param);
void	draw_ceiling_floor(t_game *game);
void	cast_rays(t_game *game);
void	normalize_angle(double *angle);
void	cast_single_ray(t_game *game, int x, double ray_angle);
void	setup_dda(t_game *game, double *side_dist_x, double *side_dist_y,
			int *step_x, int *step_y, double ray_dir_x, double ray_dir_y,
			int map_x, int map_y);
void	perform_dda(t_game *game, int *hit, int *side, int *map_x, int *map_y,
			double *side_dist_x, double *side_dist_y,
			double delta_dist_x, double delta_dist_y,
			int step_x, int step_y);
void	render_wall(t_game *game, int x, double ray_angle,
			double ray_dir_x, double ray_dir_y,
			int map_x, int map_y, int side, int step_x, int step_y);
void	calculate_wall_drawing(t_game *game, int x, double ray_angle,
			double ray_dir_x, double ray_dir_y,
			double true_dist, double perp_wall_dist,
			int side, int step_x, int step_y);
void	select_texture_and_draw(t_game *game, int x, double ray_dir_x,
			double ray_dir_y, double true_dist, int line_height,
			int draw_start, int draw_end, int side);
void	draw_textured_line(t_game *game, int x, int tex_num, double wall_x,
			int side, double ray_dir_x, double ray_dir_y,
			int line_height, int draw_start, int draw_end);
void	draw_vertical_line(t_game *game, int x, int tex_num, int tex_x,
			int tex_width, int tex_height,
			int line_height, int draw_start, int draw_end);

// Game setup and cleanup
void	setup_and_run_game(t_game *game);
void	cleanup_game(t_game *game);
void	*ft_malloc(size_t size);

#endif