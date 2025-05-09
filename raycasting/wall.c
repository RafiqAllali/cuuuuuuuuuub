#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

// Calculate and render wall
void render_wall(t_game *game, int x, double ray_angle, 
                double ray_dir_x, double ray_dir_y, 
                int map_x, int map_y, int side, int step_x, int step_y)
{
    // Calculate distance to wall
    double true_dist;
    if (side == 0)
        true_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
    else
        true_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
    
    // Calculate perpendicular wall distance for rendering
    double perp_wall_dist = true_dist * cos(ray_angle - game->player.angle);
    
    // Calculate wall drawing parameters
    calculate_wall_drawing(game, x, ray_angle, ray_dir_x, ray_dir_y, 
                          true_dist, perp_wall_dist, side, step_x, step_y);
}

// Calculate wall drawing parameters
void calculate_wall_drawing(t_game *game, int x, double ray_angle, 
                          double ray_dir_x, double ray_dir_y,
                          double true_dist, double perp_wall_dist, 
                          int side, int step_x, int step_y)
{
    (void)step_x;  // Unused variable, can be removed if not needed
    (void)step_y;  // Unused variable, can be removed if not needed
    (void)ray_angle;  // Unused variable, can be removed if not needed
    // Calculate height of line to draw on screen
    int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
    
    // Calculate lowest and highest pixel to fill in current stripe
    int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_start < 0)
        draw_start = 0;
    int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
    if (draw_end >= SCREEN_HEIGHT)
        draw_end = SCREEN_HEIGHT - 1;
    
    // Select texture and calculate texture coordinates
    select_texture_and_draw(game, x, ray_dir_x, ray_dir_y, true_dist, 
                           line_height, draw_start, draw_end, side);
}