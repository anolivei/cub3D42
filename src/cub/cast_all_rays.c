/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:00:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/10 03:10:49 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

const int map2 [MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

float		normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

static void	setup_hor_rays(t_hor *hor)
{
	hor->found_hor_wall_hit = FALSE;
	hor->hor_wall_hit_x = 0;
	hor->hor_wall_hit_y = 0;
	hor->hor_wall_content = 0;
}

void		cast_ray(float ray_angle, int strip_id, t_all *all)
{
	ray_angle = normalize_angle(ray_angle);
	all->rayaux.is_ray_fac_down = ray_angle > 0 && ray_angle < PI;
	all->rayaux.is_ray_fac_up = !all->rayaux.is_ray_fac_down;
	all->rayaux.is_ray_fac_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	all->rayaux.is_ray_fac_left = !all->rayaux.is_ray_fac_right;
	/*
	** Horizontal
	*/
	setup_hor_rays(&all->hor);
	all->rayaux.y_interc = floor (all->player.y / TILE_SIZE * TILE_SIZE);
	all->rayaux.y_interc += all->rayaux.is_ray_fac_down ? TILE_SIZE : 0;
	all->rayaux.x_interc = all->player.x + (all->rayaux.y_interc - all->player.y) / tan(ray_angle);
	all->rayaux.y_step = TILE_SIZE;
	all->rayaux.y_step *= all->rayaux.is_ray_fac_up ? -1 : 1;
	all->rayaux.x_step = TILE_SIZE / tan(ray_angle);
	all->rayaux.x_step *= (all->rayaux.is_ray_fac_left && all->rayaux.x_step > 0) ? -1 : 1;
	all->rayaux.x_step *= (all->rayaux.is_ray_fac_right && all->rayaux.x_step < 0) ? -1 : 1;
	all->hor.next_hor_touch_x = all->rayaux.x_interc;
	all->hor.next_hor_touch_y = all->rayaux.y_interc;
	while (all->hor.next_hor_touch_x >= 0 && all->hor.next_hor_touch_x <= WIN_WIDTH &&
		all->hor.next_hor_touch_y >= 0 && all->hor.next_hor_touch_x <= WIN_HEIGHT)
	{
		all->hor.x_to_check = all->hor.next_hor_touch_x;
		all->hor.y_to_check = all->hor.next_hor_touch_y + (all->rayaux.is_ray_fac_up ? -1 : 0);
		if (has_wall_at(all->hor.x_to_check, all->hor.y_to_check))
		{
			// found the wall hit
			all->hor.hor_wall_hit_x = all->hor.next_hor_touch_x;
			all->hor.hor_wall_hit_y = all->hor.next_hor_touch_y;
			all->hor.hor_wall_content = map2[(int)floor(all->hor.y_to_check / TILE_SIZE)][(int)floor(all->hor.x_to_check / TILE_SIZE)];
			all->hor.found_hor_wall_hit = TRUE;
			break;
		}
		else
		{
			all->hor.next_hor_touch_x += all->rayaux.x_step;
			all->hor.next_hor_touch_y += all->rayaux.y_step;
		}
	}
	strip_id = strip_id + 1;
	/*
	** Vertical
	*/
}

void		cast_all_rays(t_all *all)
{
	float	ray_angle;
	int		strip_id;

	ray_angle = all->player.rot_angle - (FOV / 2);
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_id, all);
		ray_angle += FOV / NUM_RAYS;
		strip_id++;
	}
}