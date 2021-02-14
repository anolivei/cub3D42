# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anolivei <anolivei@student.42sp.org>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 18:58:03 by anolivei          #+#    #+#              #
#    Updated: 2020/11/08 01:45:15 by anolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D
NAME_MAC =		cub3D_MAC

HEADER_DIR =	includes
SRC_DIR =		src
OBJ_DIR	=		.obj

LIBFT_DIR =		libft
LIBFT =			$(LIBFT_DIR)/libft.a

MLX_LINUX_DIR =	minilibx-linux
MLX_MAC_DIR =	minilibx-mac

MLX_LINUX =	$(MLX_LINUX_DIR)/libmlx.a
MLX_MAC =	$(MLX_MAC_DIR)/libmlx.dylib

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c \
		$(SRC_DIR)/ft_allocate_map.c \
		$(SRC_DIR)/ft_verify_data.c \
		$(SRC_DIR)/ft_setup_data.c \
		$(SRC_DIR)/ft_draw_minimap.c \
		$(SRC_DIR)/ft_keyboard_commands.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

HEADER_LINUX =	-I./$(HEADER_DIR) -I./$(MLX_LINUX_DIR) -I./$(LIBFT_DIR)
HEADER_MAC =	-I./$(HEADER_DIR) -I./$(MLX_MAC_DIR) -I./$(LIBFT_DIR)

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LINUX_FLAGS = -lXext -lX11 -lbsd -lm \
				-L ./$(LIBFT_DIR) -lft \
				-L ./$(MLX_LINUX_DIR) -lmlx

MAC_FLAGS = -framework OpenGL -framework AppKit -lm \
			-L ./$(LIBFT_DIR) -lft \
			-L ./$(MLX_MAC_DIR) -lmlx

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LINUX)
		clang $(OBJ) $(HEADER_LINUX) $(CFLAGS) $(LINUX_FLAGS) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				clang -c $(CFLAGS) $(HEADER_LINUX) $(HEADER_MAC) $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX_LINUX):
	make -C $(MLX_LINUX_DIR)

$(MLX_MAC):
	make -C $(MLX_MAC_DIR)
	cp $(MLX_MAC) ./

mac: $(NAME_MAC)

$(NAME_MAC): $(OBJ) $(LIBFT) $(MLX_MAC)
		gcc -I. -L. $(LIBFT) $(OBJ) $(HEADER_MAC) $(CFLAGS) $(MAC_FLAGS) -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_LINUX_DIR)
	make clean -C $(MLX_MAC_DIR)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	/bin/rm -f $(NAME) $(NAME_MAC) ./libmlx.dylib

re: fclean all

.PONY: all clean fclean re mac
