/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_intersections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:56:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 01:01:07 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	vertical_intersections2(t_all *all, int max_width, int max_height)
{
	while (all->ver.next_touch_x >= 0 && all->ver.next_touch_x <= max_width
		&& all->ver.next_touch_y >= 0 && all->ver.next_touch_y <= max_height)
	{
		all->ver.y_to_check = all->ver.next_touch_y;
		if (all->intsc.is_ray_fac_left)
			all->ver.x_to_check = all->ver.next_touch_x - 1;
		else
			all->ver.x_to_check = all->ver.next_touch_x;
		if (has_colision_at(all, all->ver.x_to_check, all->ver.y_to_check, '1'))
		{
			all->ver.wall_hit_x = all->ver.next_touch_x;
			all->ver.wall_hit_y = all->ver.next_touch_y;
			all->ver.wall_content = all->data.map[(int)floor(all->ver.y_to_check
					/ all->data.tile_size)][(int)floor(all->ver.x_to_check
					/ all->data.tile_size)];
			all->ver.found_wall_hit = true;
			break ;
		}
		all->ver.next_touch_x += all->ver.x_step;
		all->ver.next_touch_y += all->ver.y_step;
	}
}

void	vertical_intersections(t_all *all, float ray_angle)
{
	int	max_width;
	int	max_height;

	setup_rays(&all->ver);
	all->ver.x_interc = floor(all->player.x / all->data.tile_size)
		* all->data.tile_size;
	if (all->intsc.is_ray_fac_right)
		all->ver.x_interc += all->data.tile_size;
	all->ver.y_interc = all->player.y + (all->ver.x_interc - all->player.x)
		* tan(ray_angle);
	all->ver.x_step = all->data.tile_size;
	if (all->intsc.is_ray_fac_left)
		all->ver.x_step *= -1;
	all->ver.y_step = all->data.tile_size * tan(ray_angle);
	if (all->intsc.is_ray_fac_up && all->ver.y_step > 0)
		all->ver.y_step *= -1;
	if (all->intsc.is_ray_fac_down && all->ver.y_step < 0)
		all->ver.y_step *= -1;
	all->ver.next_touch_x = all->ver.x_interc;
	all->ver.next_touch_y = all->ver.y_interc;
	max_width = all->data.tile_size * all->data.len_x_map - 1;
	max_height = all->data.tile_size * all->data.len_y_map - 1;
	vertical_intersections2(all, max_width, max_height);
}
