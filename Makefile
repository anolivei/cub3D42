# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 18:58:03 by anolivei          #+#    #+#              #
#    Updated: 2021/03/04 00:25:56 by anolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D
NAME_MAC =		cub3D_MAC

HEADER_DIR =	includes
CUB_DIR =		src/cub
GNL_DIR = 		src/gnl
LIB_DIR =		src/libft
OBJ_DIR	=		.obj

SRC =	$(CUB_DIR)/main.c \
		$(CUB_DIR)/mlx_utils.c \
		$(CUB_DIR)/draw_square.c \
		$(CUB_DIR)/render_map.c \
		$(GNL_DIR)/get_next_line.c \
		$(GNL_DIR)/get_next_line_utils.c \
		$(LIB_DIR)/ft_putstr_fd.c

OBJ = $(patsubst $(CUB_DIR) $(LIB_DIR) $(GNL_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LINUX_FLAGS = -lXext -lX11 -lbsd -lm -lmlx

MAC_FLAGS = -framework OpenGL -framework AppKit -lm -lmlx

all: $(NAME)

$(NAME): $(OBJ)
		gcc -I. -L. $(OBJ) $(CFLAGS) $(MAC_FLAGS) -o $@

$(OBJ_DIR)/%.o : $(CUB_DIR) $(LIB_DIR) $(GNL_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				clang -c $(CFLAGS) $< -o $@

linux: $(NAME_LINUX)

$(NAME_LINUX): $(OBJ)
		clang $(OBJ) $(CFLAGS) $(LINUX_FLAGS) -o $@

debug: 
	gcc -g -lm -lmlx -fsanitize=address -framework OpenGL -framework AppKit $(SRC) -Wall -Wextra -Werror  -o "cub3D_debug"

debug_linux:
	gdd -g -lXext -lX11 -lbsd -lm -lmlx $(SRC) -Wall -Wextra -Werror  -o "cub3D_debug"

clean:
	/bin/rm -rf $(OBJ_DIR) cub3D.dSYM cub3D_debug.dSYM

fclean: clean
	/bin/rm -f $(NAME) $(NAME_LINUX) cub3D_debug

re: fclean all

.PONY: all clean fclean re debug
