/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:25 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/04 23:25:38 by anolivei         ###   ########.fr       */
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
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}

void	clean_old_square(t_all *all)
{
	int x;
	int y;

	x = all->map.tile_x - 2;
	y = all->map.tile_y - 2;
	while (x <= 32 + all->map.tile_x)
	{
		put_pixel(&all->img, x, y, 0x000000);
		x++;
	}
	x = all->map.tile_x - 2;
	while (y <= 32 + all->map.tile_y)
	{
		put_pixel(&all->img, x, y, 0x000000);
		y++;
	}
}
