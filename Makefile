# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 18:58:03 by anolivei          #+#    #+#              #
#    Updated: 2021/05/15 22:44:49 by anolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D_mac
NAME_LINUX =	cub3D

HEADER_DIR =	includes
CUB_DIR =		src/cub
GNL_DIR = 		src/gnl
LIB_DIR =		src/libft
OBJ_DIR	=		.obj

SRC =	$(CUB_DIR)/main.c \
		$(CUB_DIR)/setups.c \
		$(CUB_DIR)/mlx_utils.c \
		$(CUB_DIR)/draw_square.c \
		$(CUB_DIR)/draw_all_rays.c \
		$(CUB_DIR)/cub_utils.c \
		$(CUB_DIR)/render_map.c \
		$(CUB_DIR)/render_sprites.c \
		$(CUB_DIR)/render_sprites2.c \
		$(CUB_DIR)/generate_3d_projection.c \
		$(CUB_DIR)/move_player.c \
		$(CUB_DIR)/process_input.c \
		$(CUB_DIR)/cast_all_rays.c \
		$(CUB_DIR)/read_cub.c \
		$(CUB_DIR)/allocate_map.c \
		$(CUB_DIR)/colors.c \
		$(CUB_DIR)/save_image_bmp.c \
		$(CUB_DIR)/vertical_intersections.c \
		$(CUB_DIR)/horizontal_intersections.c \
		$(CUB_DIR)/verify_file.c \
		$(CUB_DIR)/exit_failure.c \
		$(CUB_DIR)/verify_texture.c \
		$(CUB_DIR)/put_data_on_struct.c \
		$(GNL_DIR)/get_next_line.c \
		$(LIB_DIR)/ft_putstr_fd.c \
		$(LIB_DIR)/ft_atoi.c \
		$(LIB_DIR)/ft_split.c \
		$(LIB_DIR)/ft_strjoin.c \
		$(LIB_DIR)/ft_strncmp.c \
		$(LIB_DIR)/ft_strlen.c \
		$(LIB_DIR)/ft_memcmp.c \
		$(LIB_DIR)/ft_memset.c \
		$(LIB_DIR)/ft_substr.c \
		$(LIB_DIR)/ft_strdup.c \
		$(LIB_DIR)/ft_strlcpy.c \
		$(LIB_DIR)/ft_bzero.c \
		$(LIB_DIR)/ft_isdigit.c

OBJ = $(patsubst $(CUB_DIR) $(LIB_DIR) $(GNL_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror -g

LINUX_FLAGS = -lXext -lX11 -lbsd -lm -lmlx

MAC_FLAGS = -framework OpenGL -framework AppKit -lm -lmlx

all: $(NAME_LINUX)

mac: $(NAME)
	./$(NAME) map.cub

$(NAME): $(OBJ)
		gcc -I. -L. $(OBJ) $(CFLAGS) $(MAC_FLAGS) -g -fsanitize=address -o $@

$(OBJ_DIR)/%.o : $(CUB_DIR) $(LIB_DIR) $(GNL_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				clang -c $(CFLAGS) $< -o $@

$(NAME_LINUX): $(OBJ)
		clang $(OBJ) $(CFLAGS) $(LINUX_FLAGS) -o $@

debug:
	gcc -g -lm -lmlx -fsanitize=address -framework OpenGL -framework AppKit $(SRC) -Wall -Wextra -Werror  -o "cub3D_debug"

debug_linux:
	gdd -g -lXext -lX11 -lbsd -lm -lmlx $(SRC) -Wall -Wextra -Werror  -o "cub3D_debug"

clean:
	/bin/rm -rf $(OBJ_DIR) cub3D.dSYM cub3D_debug.dSYM cub3D_mac.dSYM

fclean: clean
	/bin/rm -f $(NAME) $(NAME_LINUX) cub3D_debug

re: fclean all

.PONY: all clean fclean re debug debug_linux
