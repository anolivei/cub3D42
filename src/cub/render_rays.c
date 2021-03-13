/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:16:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/13 00:48:44 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void draw_line_ray(float x1, float y1, float x2, float y2, int i, t_all *all)
{
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	while ((x1 <= x2) && (y1 >= y2))
	{
		put_pixel(&all->img, (int)x1, (int)y1, BLUE);
		x1 = x1 + cos(all->ray[i].ray_angle);
		y1 = y1 + sin(all->ray[i].ray_angle);
	}
}

void	render_rays(t_all *all)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_line_ray(
			all->player.x,
			all->player.y,
			all->ray[i].wall_hit_x,
			all->ray[i].wall_hit_y,
			i,
			all);
		i++;
	}
}