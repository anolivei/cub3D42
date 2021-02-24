/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:47:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/24 01:01:18 by anolivei         ###   ########.fr       */
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
# define PI 3.1416
# define RADIUS_PLAYER 4
# define PIXEL_LEN 10
# define FALSE 0
# define TRUE 1

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

/*
** STRUCTS
*/
typedef struct	s_mlx
{
	void		*window;
	void		*init;
	void		*image;
}				t_mlx;

/*
** CUB FUNCTIONS
*/
int				initialize_window(t_mlx *mlx);
int				destroy_window(int keycode, t_mlx *mlx);
void			setup(void);
void			update(void);

/*
** LIB FUNCTIONS
*/
void			ft_putstr_fd(char *s, int fd);
#endif
