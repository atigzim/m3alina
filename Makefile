NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c \
	  srcs/parsing.c \
	  srcs/parse_utils.c \
	  srcs/free_file.c \
	  srcs/parsing_map_utils.c \
	  srcs/parsing_map.c \
	  srcs/raycast.c \
	  srcs/raycast_utils.c \
	  srcs/init_all.c \
	  srcs/move_player.c \
	  srcs/parse_textue.c\
	  srcs/load_textures.c \
	  srcs/draw_map.c \
	  srcs/file_main.c \

OBJ = $(SRC:.c=.o)

INCLUDES = -Iinclude -Ilibft 
MLX_LIB = -lmlx -lX11 -lXext -lm

LIBFT = libft/libft.a

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
.PHONY: all clean fclean re
