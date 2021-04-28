/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:22:17 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/27 22:05:04 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	draw_ray_0_90(t_all *all, float x_init, float y_init, int i)
{
	float	x_end;
	float	y_end;
	float	angle;
	float	size;

	angle = normalize_angle(all->ray[i].ray_angle);
	size = all->ray[i].distance;
	x_end = x_init + cos(angle) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(angle) * size * MINIMAP_SCALE_FACTOR;
	while ((x_init <= x_end) && (y_init <= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(angle) * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(angle) * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_ray_90_180(t_all *all, float x_init, float y_init, int i)
{
	float	x_end;
	float	y_end;
	float	angle;
	float	size;

	angle = normalize_angle(all->ray[i].ray_angle);
	size = all->ray[i].distance;
	x_end = x_init + cos(angle) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(angle) * size * MINIMAP_SCALE_FACTOR;
	while ((x_init >= x_end) && (y_init <= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(angle) * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(angle) * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_ray_180_270(t_all *all, float x_init, float y_init, int i)
{
	float	x_end;
	float	y_end;
	float	angle;
	float	size;

	angle = normalize_angle(all->ray[i].ray_angle);
	size = all->ray[i].distance;
	x_end = x_init + cos(angle) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(angle) * size * MINIMAP_SCALE_FACTOR;
	while ((x_init >= x_end) && (y_init >= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(angle) * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(angle) * MINIMAP_SCALE_FACTOR;
	}
}

static void	draw_ray_270_360(t_all *all, float x_init, float y_init, int i)
{
	float	x_end;
	float	y_end;
	float	angle;
	float	size;

	angle = normalize_angle(all->ray[i].ray_angle);
	size = all->ray[i].distance;
	x_end = x_init + cos(angle) * size * MINIMAP_SCALE_FACTOR;
	y_end = y_init + sin(angle) * size * MINIMAP_SCALE_FACTOR;
	while ((x_init <= x_end) && (y_init >= y_end))
	{
		put_pixel(&all->img, (int)x_init, (int)y_init, BLUE);
		x_init = x_init + cos(angle) * MINIMAP_SCALE_FACTOR;
		y_init = y_init + sin(angle) * MINIMAP_SCALE_FACTOR;
	}
}

void		draw_all_rays(t_all *all, int i)
{
	float	x_init;
	float	y_init;
	float	angle_norm;

	x_init = all->player.x * MINIMAP_SCALE_FACTOR;
	y_init = all->player.y * MINIMAP_SCALE_FACTOR;
	angle_norm = normalize_angle(all->ray[i].ray_angle);
	if (angle_norm >= 0 && angle_norm <= (90 * (PI / 180)))
		draw_ray_0_90(all, x_init, y_init, i);
	if (angle_norm > (90 * (PI / 180)) && angle_norm <= (180 * (PI / 180)))
		draw_ray_90_180(all, x_init, y_init, i);
	if (angle_norm > (180 * (PI / 180)) && angle_norm <= (270 * (PI / 180)))
		draw_ray_180_270(all, x_init, y_init, i);
	if (angle_norm > (270 * (PI / 180)) && angle_norm <= (360 * (PI / 180)))
		draw_ray_270_360(all, x_init, y_init, i);
}
