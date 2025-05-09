#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

// The core raycasting algorithm
void cast_rays(t_game *game)
{
    // Clear the image and draw ceiling/floor
    draw_ceiling_floor(game);
    
    // Cast a ray for each column of the screen
    int x = 0;
    while (x < SCREEN_WIDTH)
    {
        // Calculate ray direction
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        double ray_angle = game->player.angle + (FOV / 2) * DEG_TO_RAD * camera_x;
        
        // Normalize ray angle
        normalize_angle(&ray_angle);
        
        // Cast single ray
        cast_single_ray(game, x, ray_angle);
        x++;
    }
}

// Cast a single ray
void cast_single_ray(t_game *game, int x, double ray_angle)
{
    // Ray direction vectors
    double ray_dir_x = cos(ray_angle);
    double ray_dir_y = sin(ray_angle);
    
    // Player's grid position
    int map_x = (int)game->player.x;
    int map_y = (int)game->player.y;
    
    // DDA variables
    double side_dist_x, side_dist_y;
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
    int step_x, step_y;
    
    // Setup DDA
    setup_dda(game, &side_dist_x, &side_dist_y, &step_x, &step_y, 
              ray_dir_x, ray_dir_y, map_x, map_y);
    
    // Perform DDA
    int hit = 0;  // was a wall hit?
    int side;     // was a NS or a EW wall hit?
    
    perform_dda(game, &hit, &side, &map_x, &map_y, 
                &side_dist_x, &side_dist_y, delta_dist_x, delta_dist_y, step_x, step_y);
    
    // Calculate distance and render wall
    render_wall(game, x, ray_angle, ray_dir_x, ray_dir_y, map_x, map_y, side, step_x, step_y);
}