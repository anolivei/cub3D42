/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:25 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/01 22:00:08 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_square(t_all *all)
{
	int	x;
	int	y;

	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	x = all->player.x;
	y = all->player.y;
	while (x <= (32 + all->player.x))
	{
		while (y <= (32 + all->player.y))
		{
			clean_old_square(all);
			put_pixel(&all->img, x, y, 0xFFFF00);
			y++;
		}
		x++;
		y = all->player.y;
	}
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}

void	clean_old_square(t_all *all)
{
	int x;
	int y;

	x = all->player.x - 2;
	y = all->player.y - 2;
	while (x <= 32 + all->player.x)
	{
		put_pixel(&all->img, x, y, 0x000000);
		x++;
	}
	x = all->player.x - 2;
	while (y <= 32 + all->player.y)
	{
		put_pixel(&all->img, x, y, 0x000000);
		y++;
	}
}
