/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:47:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/13 19:14:23 by anolivei         ###   ########.fr       */
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
# include <limits.h>
# include <stdio.h>
# include <float.h>
# include <stdbool.h>
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
# define TEXT_WIDTH 32
# define TEXT_HEIGHT 32
# define NUM_SPRITE 5
# define FOV (60 * (PI/180))
# define NUM_RAYS WIN_WIDTH
# define MINIMAP_SCALE_FACTOR 0.3

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
typedef struct	s_img
{
	void		*img_ptr;
	char		*addr;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct	s_text
{
	t_img		sprite;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
}				t_text;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		distance;
	float		angle;
	bool		visible;
	t_img		sprite;
}				t_sprite;

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
	int			turn_dir; /* -1 for turn left, +1 for turn right */
	int			walk_dir; /* -1 for back, +1 for front */
	int			walk_dir_side; /* -1 for left, +1 for right */
	float		rot_angle;
	float		walk_speed;
	float		turn_speed;
}				t_player;

typedef struct	s_intsc
{
	int			found_wall_hit;
	float		wall_hit_x;
	float		wall_hit_y;
	int			wall_content;
	float		next_touch_x;
	float		next_touch_y;
	float		x_to_check;
	float		y_to_check;
	float		x_interc;
	float		y_interc;
	float		x_step;
	float		y_step;
	int			is_ray_fac_down;
	int			is_ray_fac_up;
	int			is_ray_fac_right;
	int			is_ray_fac_left;
	float		hit_distance;
}				t_intsc;

typedef struct	s_ray
{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		distance;
	int			hit_vert;
	int			ray_up;
	int			ray_down;
	int			ray_left;
	int			ray_right;
	int			wall_hit_content;
}				t_ray[NUM_RAYS];

typedef struct	s_map
{
	int			wall_color;
	int			floor_color;
	int			tile_color;
	int 		tile_x;
	int			tile_y;
	char		*line;
}				t_map;

typedef struct	s_all
{
	t_text		text;
	t_sprite	sprite[NUM_SPRITE];
	t_intsc		intsc;
	t_intsc		hor;
	t_intsc		ver;
	t_img		img;
	t_player	player;
	t_mlx		mlx;
	t_map		map;
	t_ray		ray;
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
void			setup_player(t_player *player);
void			setup_texture(t_all *all, t_text *text);
void			put_pixel(t_img *data, int x, int y, int color);
int				pick_pixel(t_img *data, int x, int y);

void			render(t_all *all);
void			render_map(t_all *all);
void			render_player(t_all *all);
void			render_rays(t_all *all);
void			generate_3d_projection(t_all *all);
void			render_sprites_projection(t_all *all);
void			render_sprites_map(t_all *all);
void			render_visible_sprites(t_all *all, t_sprite *visible_sprite, int num_visible_sprites);
t_sprite		*sort_sprites(t_sprite *visible_sprite, int num_visible_sprite);

void			move_player(t_player *player);
int				has_wall_at(float x, float y);
int				has_sprite_at(float x, float y);

void			cast_all_rays(t_all *all);
void			cast_ray(float ray_angle, int strip_id, t_all *all);
float			normalize_angle(float angle);
float			distance_between_points(int x1, int y1, int x2, int y2);
void			draw_square(t_all *all, int draw_x, int draw_y, int size);
void			draw_all_rays(t_all *all, int i);

int				read_cub(t_all *all, char *file);

/*
** LIB FUNCTIONS
*/
void			ft_putstr_fd(char *s, int fd);

#endif
