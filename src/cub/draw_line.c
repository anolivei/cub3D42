/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:09:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/07 20:59:22 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	draw_line_0_45(t_all *all, float x_init, float y_init, int size)
{
	float	x_end;
	float	y_end;

	x_end = x_init + cos(all->player.rot_angle) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(all->player.rot_angle) * size * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	while ((x_init <= x_end) && (y_init <= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(all->player.rot_angle) * 1 * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(all->player.rot_angle) * 1 * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_line_90_180(t_all *all, float x_init, float y_init, int size)
{
	float	x_end;
	float	y_end;

	x_end = x_init - (cos(all->player.rot_angle) * -1) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(all->player.rot_angle) * size * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	while ((x_init >= x_end) && (y_init <= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init - (cos(all->player.rot_angle) * -1) * 1 * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(all->player.rot_angle) * 1 * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_line_180_270(t_all *all, float x_init, float y_init, int size)
{
	float	x_end;
	float	y_end;

	x_end = x_init - (cos(all->player.rot_angle) * -1) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init - (sin(all->player.rot_angle) * -1) * size * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	while ((x_init >= x_end) && (y_init >= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init - (cos(all->player.rot_angle) * -1) * 1 * MINIMAP_SCALE_FACTOR;
		y_init = y_init - (sin(all->player.rot_angle) * -1) * 1 * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_line_270_360(t_all *all, float x_init, float y_init, int size)
{
	float	x_end;
	float	y_end;

	x_end = x_init + (cos(all->player.rot_angle)) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init - (sin(all->player.rot_angle) * -1) * size * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	while ((x_init <= x_end) && (y_init >= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(all->player.rot_angle) * 1 * MINIMAP_SCALE_FACTOR;
		y_init = y_init - (sin(all->player.rot_angle) * -1) * 1 * MINIMAP_SCALE_FACTOR;
	}
}

void	draw_line(t_all *all, int size)
{
	float	x_init;
	float	y_init;
	float	angle_normalized;

	x_init = (all->player.x + all->player.height / 2) * MINIMAP_SCALE_FACTOR;
	y_init = (all->player.y + all->player.height / 2) * MINIMAP_SCALE_FACTOR;
	if (all->player.rot_angle >= 0)
		angle_normalized = all->player.rot_angle;
	else
		angle_normalized = all->player.rot_angle >= (-360 * (PI / 180)) ? 
			((2 * PI) + (all->player.rot_angle)) : 
			(((2 * PI) * (((int)((all->player.rot_angle * -1) / (2 * PI))) + 1)) + (all->player.rot_angle));
	angle_normalized = angle_normalized > (2 * PI) ? (angle_normalized - 
			(((int)(angle_normalized / (2 * PI))) * (2 * PI))) : angle_normalized;
	if (angle_normalized >= 0 && angle_normalized <= (90 * (PI / 180)))
		draw_line_0_45(all, x_init, y_init, size);
	if (angle_normalized > (90 * (PI / 180)) && angle_normalized <= (180 * (PI / 180)))
		draw_line_90_180(all, x_init, y_init, size);
	if (angle_normalized > (180 * (PI / 180)) && angle_normalized <= (270 * (PI / 180)))
		draw_line_180_270(all, x_init, y_init, size);
	if (angle_normalized > (270 * (PI / 180)) && angle_normalized <= (360 * (PI / 180)))
		draw_line_270_360(all, x_init, y_init, size);
}