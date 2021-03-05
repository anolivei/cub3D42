/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:25 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/04 21:41:18 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_square(t_all *all, int color)
{
	int	x;
	int	y;

	all->map.tile_x = all->map.tile_x * MINIMAP_SCALE_FACTOR;
	all->map.tile_y = all->map.tile_y * MINIMAP_SCALE_FACTOR;
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	x = all->map.tile_x;
	y = all->map.tile_y;
	while (x <= ((TILE_SIZE * MINIMAP_SCALE_FACTOR)+ all->map.tile_x))
	{
		while (y <= ((TILE_SIZE * MINIMAP_SCALE_FACTOR) + all->map.tile_y))
		{
			put_pixel(&all->img, x, y, color);
			y++;
		}
		x++;
		y = all->map.tile_y;
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
