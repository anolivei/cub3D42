/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:25 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/07 17:29:37 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_square(t_all *all, int draw_x, int draw_y, int size, int color)
{
	int	x;
	int	y;

	draw_x = draw_x * MINIMAP_SCALE_FACTOR;
	draw_y = draw_y * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	x = draw_x;
	y = draw_y;
	while (x <= ((size * MINIMAP_SCALE_FACTOR)+ draw_x))
	{
		while (y <= ((size * MINIMAP_SCALE_FACTOR) + draw_y))
		{
			put_pixel(&all->img, x, y, color);
			y++;
		}
		x++;
		y = draw_y;
	}
}
