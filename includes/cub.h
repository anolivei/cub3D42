/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:47:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/07 16:28:37 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/*
** INCLUDES
*/
# include <mlx.h>
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

/*
** DEFINES
*/
# define PI 3.14159265
# define TWO_PI 6.28318530
# define RADIUS_PLAYER 4
# define TILE_SIZE 32
# define MAP_NUM_ROWS 17
# define MAP_NUM_COLS 29
# define FALSE 0
# define TRUE 1
# define WIN_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WIN_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
# define FOV (60 * (PI/180))
# define NUM_RAYS WIN_WIDTH
# define MINIMAP_SCALE_FACTOR 1.0

/*
** KEYCODES MAC
*/
# define W_KEYM 13
# define S_KEYM 1
# define A_KEYM 0
# define D_KEYM 2
# define UP_ARROW_KEYM 126
# define DOWN_ARROW_KEYM 125
# define RIGHT_ARROW_KEYM 124
# define LEFT_ARROW_KEYM 123
# define TAB_KEYM 48
# define ESC_KEYM 53

/*
** KEYCODES LINUX
*/
# define W_KEYL 119
# define S_KEYL 115
# define A_KEYL 97
# define D_KEYL 100
# define UP_ARROW_KEYL 65362
# define DOWN_ARROW_KEYL 65364
# define RIGHT_ARROW_KEYL 65363
# define LEFT_ARROW_KEYL 65361
# define TAB_KEYL 65289
# define ESC_KEYL 65307

/*
** COLORS
*/
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define MAGENTA 0x00FF00FF
# define CYAN 0x0000FFFF
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
/*
** STRUCTS
*/
typedef struct	s_mlx
{
	void		*window;
	void		*init;
}				t_mlx;

typedef struct	s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turn_dir; /* -1 for left, +1 for right */
	int			walk_dir; /* -1 for back, +1 for front */
	float		rot_angle;
	float		walk_speed;
	float		turn_speed;
}				t_player;

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	char		*addr;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_map
{
	int			wall_color;
	int			floor_color;
	int 		tile_x;
	int			tile_y;
}				t_map;

typedef struct	s_all
{
	t_img		img;
	t_player	player;
	t_mlx		mlx;
	t_map		map;
}				t_all;

/*
** CUB FUNCTIONS
*/
int				initialize_window(t_all *mlx);
int				destroy_window(t_all *all);
int				key_press(int keycode, t_all *all);
int				key_release(int keycode, t_all *all);
void			process_input(t_all *all);
void			walk_turn_dir(int *walk_turn_dir, int i, t_all *all);
void			setup(t_player *player);

void			put_pixel(t_img *data, int x, int y, int color);
int				pick_pixel(t_img *data, int x, int y);

void			render(t_all *all);
void			render_map(t_all *all);
void			render_player(t_all *all);
void			move_player(t_player *player);

void			draw_square(t_all *all, int draw_x, int draw_y, int size, int color);
void			clean_old_square(t_all *all);
void			draw_line(t_all *all, int size);

/*
** LIB FUNCTIONS
*/
void			ft_putstr_fd(char *s, int fd);
#endif
