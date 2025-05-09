#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

// Select texture and calculate texture coordinates
void select_texture_and_draw(t_game *game, int x, double ray_dir_x, double ray_dir_y,
                            double true_dist, int line_height, 
                            int draw_start, int draw_end, int side)
{
    // Texture selection based on wall direction
    int tex_num;
    if (side == 0)
    {
        if (ray_dir_x > 0)
            tex_num = EAST;
        else
            tex_num = WEST;
    }
    else
    {
        if (ray_dir_y > 0)
            tex_num = SOUTH;
        else
            tex_num = NORTH;
    }
    
    // Calculate exact hit point on wall
    double wall_x;
    if (side == 0)
        wall_x = game->player.y + true_dist * ray_dir_y;
    else
        wall_x = game->player.x + true_dist * ray_dir_x;
    wall_x -= floor(wall_x);
    
    draw_textured_line(game, x, tex_num, wall_x, side, ray_dir_x, ray_dir_y,
                      line_height, draw_start, draw_end);
}