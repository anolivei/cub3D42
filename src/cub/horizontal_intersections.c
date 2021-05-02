/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_intersections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 23:56:42 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 00:57:52 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	horizontal_intersections2(t_all *all, int max_width, int max_height)
{
	while (all->hor.next_touch_x >= 0 && all->hor.next_touch_x <= max_width
		&& all->hor.next_touch_y >= 0 && all->hor.next_touch_y <= max_height)
	{
		all->hor.x_to_check = all->hor.next_touch_x;
		if (all->intsc.is_ray_fac_up)
			all->hor.y_to_check = all->hor.next_touch_y - 1;
		else
			all->hor.y_to_check = all->hor.next_touch_y;
		if (has_colision_at(all, all->hor.x_to_check, all->hor.y_to_check, '1'))
		{
			all->hor.wall_hit_x = all->hor.next_touch_x;
			all->hor.wall_hit_y = all->hor.next_touch_y;
			all->hor.wall_content = all->data.map[(int)floor(all->hor.y_to_check
					/ all->data.tile_size)][(int)floor(all->hor.x_to_check
					/ all->data.tile_size)];
			all->hor.found_wall_hit = TRUE;
			break ;
		}
		all->hor.next_touch_x += all->hor.x_step;
		all->hor.next_touch_y += all->hor.y_step;
	}
}

void	horizontal_intersections(t_all *all, float ray_angle)
{
	int	max_width;
	int	max_height;

	setup_rays(&all->hor);
	all->hor.y_interc = floor (all->player.y / all->data.tile_size)
		* all->data.tile_size;
	if (all->intsc.is_ray_fac_down)
		all->hor.y_interc += all->data.tile_size;
	all->hor.x_interc = all->player.x + (all->hor.y_interc - all->player.y)
		/ tan(ray_angle);
	all->hor.y_step = all->data.tile_size;
	if (all->intsc.is_ray_fac_up)
		all->hor.y_step *= -1;
	all->hor.x_step = all->data.tile_size / tan(ray_angle);
	if (all->intsc.is_ray_fac_left && all->hor.x_step > 0)
		all->hor.x_step *= -1;
	if (all->intsc.is_ray_fac_right && all->hor.x_step < 0)
		all->hor.x_step *= -1;
	max_width = all->data.tile_size * all->data.len_x_map;
	max_height = all->data.tile_size * all->data.len_y_map;
	all->hor.next_touch_x = all->hor.x_interc;
	all->hor.next_touch_y = all->hor.y_interc;
	horizontal_intersections2(all, max_width, max_height);
}
