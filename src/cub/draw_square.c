/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 20:38:25 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/28 23:31:27 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	draw_square(t_all *all)
{
	int	x;
	int	y;

	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	x = 0;
	y = 0;
	while (x <= 32)
	{
		while (y <= 32)
		{
			put_pixel(&all->img, x, y, 0xFFFFFF);
			y++;
		}
		x++;
		y = 0;
	}
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}
