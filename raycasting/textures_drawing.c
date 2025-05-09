#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"
void draw_textured_line(t_game *game, int x, t_wall *wall, t_ray *ray, int side)
{
    // Get texture dimensions
    wall->tex_width = game->textures[wall->tex_num]->width;
    wall->tex_height = game->textures[wall->tex_num]->height;
    
    // Calculate texture x coordinate
    wall->tex_x = (int)(wall->wall_x * wall->tex_width);
    if ((side == 0 && ray->dir_x > 0) || (side == 1 && ray->dir_y < 0))
        wall->tex_x = wall->tex_width - wall->tex_x - 1;
    
    // Ensure texture coordinates stay within bounds
    if (wall->tex_x < 0) wall->tex_x = 0;
    if (wall->tex_x >= wall->tex_width) wall->tex_x = wall->tex_width - 1;
    
    draw_vertical_line(game, x, wall);
}

// Draw vertical line with texture
void draw_vertical_line(t_game *game, int x, t_wall *wall)
{
    uint32_t *pixels = (uint32_t *)game->img->pixels;
    
    // Calculate texture step and position
    double step = (double)wall->tex_height / wall->line_height;
    double tex_pos = (wall->draw_start - SCREEN_HEIGHT / 2 + wall->line_height / 2) * step;
    
    int y = wall->draw_start;
    while (y < wall->draw_end)
    {
        // Cast to integer and ensure we stay within texture bounds
        int tex_y = (int)tex_pos % wall->tex_height;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= wall->tex_height) tex_y = wall->tex_height - 1;
        tex_pos += step;
        
        // Get pixel color from texture
        int pixel_index = (tex_y * wall->tex_width + wall->tex_x) * 4;
        if (pixel_index < 0 || pixel_index >= (wall->tex_width * wall->tex_height * 4))
            pixel_index = 0; // Use first pixel as fallback
            
        uint8_t *pixel = &game->textures[wall->tex_num]->pixels[pixel_index];
        
        // Fixed color byte ordering for texture pixels
        uint32_t color = (pixel[3] << 24) | (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
        
        // Draw pixel
        pixels[y * SCREEN_WIDTH + x] = color;
        y++;
    }
}