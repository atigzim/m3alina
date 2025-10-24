NAME = CUB_3D

CC = cc

CFLAGS = -Wall -Wextra -Werror  

SRC = main.c
INCLUDE = cub_3d.h
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
all: $(NAME) 

$(NAME) : $(OBJ) $(INCLUDE) $(LIBFT)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)