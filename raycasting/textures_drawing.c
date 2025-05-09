#include "/Users/rallali/Desktop/cuuuuu/include/cub3d.h"

// Draw textured vertical line
void draw_textured_line(t_game *game, int x, int tex_num, double wall_x, 
                       int side, double ray_dir_x, double ray_dir_y,
                       int line_height, int draw_start, int draw_end)
{
    // Get texture dimensions
    int tex_width = game->textures[tex_num]->width;
    int tex_height = game->textures[tex_num]->height;
    
    // Calculate texture x coordinate
    int tex_x = (int)(wall_x * tex_width);
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = tex_width - tex_x - 1;
    
    // Ensure texture coordinates stay within bounds
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= tex_width) tex_x = tex_width - 1;
    
    draw_vertical_line(game, x, tex_num, tex_x, tex_width, tex_height,
                      line_height, draw_start, draw_end);
}

// Draw vertical line with texture
void draw_vertical_line(t_game *game, int x, int tex_num, int tex_x, 
                       int tex_width, int tex_height,
                       int line_height, int draw_start, int draw_end)
{
    uint32_t *pixels = (uint32_t *)game->img->pixels;
    
    // Calculate texture step and position
    double step = (double)tex_height / line_height;
    double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
    
    int y = draw_start;
    while (y < draw_end)
    {
        // Cast to integer and ensure we stay within texture bounds
        int tex_y = (int)tex_pos % tex_height;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= tex_height) tex_y = tex_height - 1;
        tex_pos += step;
        
        // Get pixel color from texture
        int pixel_index = (tex_y * tex_width + tex_x) * 4;
        if (pixel_index < 0 || pixel_index >= (tex_width * tex_height * 4))
            pixel_index = 0; // Use first pixel as fallback
            
        uint8_t *pixel = &game->textures[tex_num]->pixels[pixel_index];
        
        // Fixed color byte ordering for texture pixels
        uint32_t color = (pixel[3] << 24) | (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
        
        // Draw pixel
        pixels[y * SCREEN_WIDTH + x] = color;
        y++;
    }
}