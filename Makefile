NAME = cub3D

SRCS = \
	main.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \
	utils/ft_split.c \
	utils/utils.c \
	parsing/config_valid.c \
	parsing/handle_colors.c \
	parsing/map_utils.c \
	parsing/map_valid.c \
	parsing/parse_utils.c \
	parsing/text_handle.c \
	raycasting/dda.c \
	raycasting/game.c \
	raycasting/movements.c \
	raycasting/key_handler.c \
	raycasting/player_init.c \
	raycasting/raycast.c \
	raycasting/render.c \
	raycasting/texture.c \
	raycasting/texture_init.c \
	raycasting/wall.c \
	raycasting/textures_drawing.c

OBJS = main.o \
	gnl/get_next_line.o \
	gnl/get_next_line_utils.o \
	utils/ft_split.o \
	utils/utils.o \
	parsing/config_valid.o \
	parsing/handle_colors.o \
	parsing/map_utils.o \
	parsing/map_valid.o \
	parsing/parse_utils.o \
	parsing/text_handle.o \
	raycasting/dda.o \
	raycasting/game.o \
	raycasting/movements.o \
	raycasting/key_handler.o \
	raycasting/player_init.o \
	raycasting/raycast.o \
	raycasting/render.o \
	raycasting/texture.o \
	raycasting/texture_init.o \
	raycasting/wall.o \
	raycasting/textures_drawing.o

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math
LDFLAGS = libmlx42.a -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
