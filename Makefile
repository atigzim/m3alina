NAME = CUB_3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c gnl/gnl.c
OBJ = $(SRC:.c=.o)
INCLUDE = cub_3d.h
LIBFT = libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(INCLUDE) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# %.o : %.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
