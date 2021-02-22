# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/27 18:58:03 by anolivei          #+#    #+#              #
#    Updated: 2021/02/21 22:46:56 by anolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			cub3D
NAME_MAC =		cub3D_MAC

HEADER_DIR =	includes
SRC_DIR =		src
OBJ_DIR	=		.obj

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/get_next_line_utils.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

LINUX_FLAGS = -lXext -lX11 -lbsd -lm -lmlx

MAC_FLAGS = -framework OpenGL -framework AppKit -lm -lmlx

all: $(NAME)

$(NAME): $(OBJ)
		gcc -I. -L. $(OBJ) $(CFLAGS) $(MAC_FLAGS) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				mkdir -p $(OBJ_DIR)
				clang -c $(CFLAGS) $< -o $@

linux: $(NAME_LINUX)

$(NAME_LINUX): $(OBJ)
		clang $(OBJ) $(HEADER_LINUX) $(LINUX_FLAGS) -o $@

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME) $(NAME_LINUX)

re: fclean all

.PONY: all clean fclean re mac
