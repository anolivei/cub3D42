/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:47:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/01 19:21:52 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

/*
** INCLUDES
*/
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <float.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

/*
** DEFINES
*/
# define BUFFER_SIZE 1000
# define PI 3.14159265
# define TWO_PI 6.28318530
# define FALSE 0
# define TRUE 1
# define FOV 1.0472
# define MINIMAP_SCALE_FACTOR 0.2

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
typedef struct s_bmp
{
	unsigned char	buff_header[54];
	int				*buff_body;
}					t_bmp;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			size_l;
	int			bpp;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_text
{
	t_img		sprite;
	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;
	int			res_text[8];
}				t_text;

typedef struct s_sprite
{
	float		x;
	float		y;
	float		distance;
	float		angle;
	bool		visible;
	t_img		sprite;
}				t_sprite;

typedef struct s_mlx
{
	void		*window;
	void		*init;
}				t_mlx;

typedef struct s_player
{
	float		x;
	float		y;
	float		width;
	float		height;
	int			turn_dir;
	int			walk_dir;
	int			walk_dir_side;
	float		rot_angle;
	float		walk_speed;
	float		turn_speed;
}				t_player;

typedef struct s_intsc
{
	int			found_wall_hit;
	float		wall_hit_x;
	float		wall_hit_y;
	char		wall_content;
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

typedef struct s_ray
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
}				t_ray;

typedef struct s_map
{
	int			wall_color;
	int			floor_color;
	int			tile_color;
	int			tile_x;
	int			tile_y;
}				t_map;

typedef struct s_data
{
	int			len_x_map;
	int			len_y_map;
	int			scr_weig;
	int			scr_heig;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	int			floor;
	int			ceil;
	char		*sprite;
	int			error;
	char		**map;
	char		*map_line;
	char		orientation;
	char		*line;
	int			num_sprites;
	int			tile_size;
}				t_data;

typedef struct s_all
{
	t_bmp		bmp;
	t_data		data;
	t_text		text;
	t_sprite	*sprite;
	t_intsc		intsc;
	t_intsc		hor;
	t_intsc		ver;
	t_img		img;
	t_player	player;
	t_mlx		mlx;
	t_map		map;
	t_ray		*ray;
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
void			setup_player(t_all *all, t_player *player);
void			setup_texture(t_all *all, t_text *text);
void			setup_map(t_all *all);
void			put_textures_in_a_array(t_text *text);
void			choose_tile_size(t_data *data, t_text *text);
void			put_pixel(t_img *data, int x, int y, int color);
int				pick_pixel(t_img *data, int x, int y);
void			render(t_all *all);
void			render_map(t_all *all);
void			render_rays(t_all *all);
void			generate_3d_projection(t_all *all);
void			render_sprites_projection(t_all *all);
void			render_sprites_map(t_all *all);
void			render_visible_sprites(t_all *all, t_sprite *visible_sprite,
					int num_visible_sprites);
t_sprite		*sort_sprites(t_sprite *visible_sprite, int num_visible_sprite);
void			move_player(t_all *all, t_player *player);
int				has_colision_at(t_all *all, float x, float y, char c);
void			cast_all_rays(t_all *all);
void			cast_ray(float ray_angle, int strip_id, t_all *all);
float			normalize_angle(float angle);
float			distance_between_points(int x1, int y1, int x2, int y2);
void			draw_square(t_all *all, int draw_x, int draw_y, int size);
void			draw_all_rays(t_all *all, int i);
int				read_cub(t_all *all, char *file, int argc, int posic);
void			verify_data(t_all *all, int posic);
int				convert_colors (char *color);
void			free_array(void **array);
void			allocate_map(t_all *all, int i, int j, int p);
void			save_image_bmp(t_all *all);

/*
** LIB FUNCTIONS
*/
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
int				count_words(const char *s, char c);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);

/*
** GNL FUNCTIONS
*/
int				get_next_line(int fd, char **line);
size_t			ft_strlen_gnl(const char *str);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin_gnl(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
size_t			ft_strlcpy(char *restrict dst,
					const char *restrict src, size_t destsize);
#endif
