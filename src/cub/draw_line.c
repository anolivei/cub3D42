/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 00:09:46 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/07 16:48:08 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_line(t_all *all, int size)
{
	float	x_init;
	float	y_init;
	float	x_end;
	float	y_end;

	x_init = (all->player.x + all->player.height / 2) * MINIMAP_SCALE_FACTOR;
	y_init = (all->player.y + all->player.height / 2) * MINIMAP_SCALE_FACTOR;
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