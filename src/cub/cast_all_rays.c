/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:00:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/09 00:25:56 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

const int map2 [MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

static void	setup_rays(t_intsc *hv)
{
	hv->found_wall_hit = FALSE;
	hv->wall_hit_x = 0;
	hv->wall_hit_y = 0;
	hv->wall_content = 0;
}

static void	horizontal_intersections(t_all *all, float ray_angle)
{
	setup_rays(&all->hor);
	all->hor.y_interc = floor (all->player.y / TILE_SIZE) * TILE_SIZE;
	all->hor.y_interc += all->intsc.is_ray_fac_down ? TILE_SIZE : 0;
	all->hor.x_interc = all->player.x + (all->hor.y_interc - all->player.y) / tan(ray_angle);
	all->hor.y_step = TILE_SIZE;
	all->hor.y_step *= all->intsc.is_ray_fac_up ? -1 : 1;
	all->hor.x_step = TILE_SIZE / tan(ray_angle);
	all->hor.x_step *= (all->intsc.is_ray_fac_left && all->hor.x_step > 0) ? -1 : 1;
	all->hor.x_step *= (all->intsc.is_ray_fac_right && all->hor.x_step < 0) ? -1 : 1;
	all->hor.next_touch_x = all->hor.x_interc;
	all->hor.next_touch_y = all->hor.y_interc;
	while (all->hor.next_touch_x >= 0 && all->hor.next_touch_x <= WIN_WIDTH &&
		all->hor.next_touch_y >= 0 && all->hor.next_touch_y <= WIN_HEIGHT)
	{
		all->hor.x_to_check = all->hor.next_touch_x;
		all->hor.y_to_check = all->hor.next_touch_y + (all->intsc.is_ray_fac_up ? -1 : 0);
		if (has_wall_at(all->hor.x_to_check, all->hor.y_to_check))
		{
			all->hor.wall_hit_x = all->hor.next_touch_x;
			all->hor.wall_hit_y = all->hor.next_touch_y;
			all->hor.wall_content = map2[(int)floor(all->hor.y_to_check / TILE_SIZE)]
				[(int)floor(all->hor.x_to_check / TILE_SIZE)];
			all->hor.found_wall_hit = TRUE;
			break;
		}
		else
		{
			all->hor.next_touch_x += all->hor.x_step;
			all->hor.next_touch_y += all->hor.y_step;
		}
	}
}

static void	vertical_intersections(t_all *all, float ray_angle)
{
	setup_rays(&all->ver);
	all->ver.x_interc = floor(all->player.x / TILE_SIZE) * TILE_SIZE;
	all->ver.x_interc += all->intsc.is_ray_fac_right ? TILE_SIZE : 0;
	all->ver.y_interc = all->player.y + (all->ver.x_interc - all->player.x) * tan(ray_angle);
	all->ver.x_step = TILE_SIZE;
	all->ver.x_step *= all->intsc.is_ray_fac_left ? -1 : 1;
	all->ver.y_step = TILE_SIZE * tan(ray_angle);
	all->ver.y_step *= (all->intsc.is_ray_fac_up && all->ver.y_step > 0) ? -1 : 1;
	all->ver.y_step *= (all->intsc.is_ray_fac_down && all->ver.y_step < 0) ? -1 : 1;
	all->ver.next_touch_x = all->ver.x_interc;
	all->ver.next_touch_y = all->ver.y_interc;
	while (all->ver.next_touch_x >= 0 && all->ver.next_touch_x <= WIN_WIDTH &&
		all->ver.next_touch_y >= 0 && all->ver.next_touch_y <= WIN_HEIGHT)
	{
		all->ver.x_to_check = all->ver.next_touch_x + (all->intsc.is_ray_fac_left ? -1 : 0);
		all->ver.y_to_check = all->ver.next_touch_y;
		if (has_wall_at(all->ver.x_to_check, all->ver.y_to_check))
		{
			all->ver.wall_hit_x = all->ver.next_touch_x;
			all->ver.wall_hit_y = all->ver.next_touch_y;
			all->ver.wall_content = map2[(int)floor(all->ver.y_to_check / TILE_SIZE)]
				[(int)floor(all->ver.x_to_check / TILE_SIZE)];
			all->ver.found_wall_hit = TRUE;
			break ;
		}
		else
		{
			all->ver.next_touch_x += all->ver.x_step;
			all->ver.next_touch_y += all->ver.y_step;
		}
	}
}

static void	verify_lower_intersection(t_all *all, float ray_angle, int strip_id)
{	
	all->hor.hit_distance = all->hor.found_wall_hit
		? distance_between_points(all->player.x, all->player.y, all->hor.wall_hit_x, all->hor.wall_hit_y) : FLT_MAX;
	all->ver.hit_distance = all->ver.found_wall_hit
		? distance_between_points(all->player.x, all->player.y, all->ver.wall_hit_x, all->ver.wall_hit_y) : FLT_MAX;
	if (all->ver.hit_distance < all->hor.hit_distance)
	{
		all->ray[strip_id].distance = all->ver.hit_distance;
		all->ray[strip_id].wall_hit_x = all->ver.wall_hit_x;
		all->ray[strip_id].wall_hit_y = all->ver.wall_hit_y;
		all->ray[strip_id].wall_hit_content = all->ver.wall_content;
		all->ray[strip_id].hit_vert = TRUE;
	}
	else
	{
		all->ray[strip_id].distance = all->hor.hit_distance;
		all->ray[strip_id].wall_hit_x = all->hor.wall_hit_x;
		all->ray[strip_id].wall_hit_y = all->hor.wall_hit_y;
		all->ray[strip_id].wall_hit_content = all->hor.wall_content;
		all->ray[strip_id].hit_vert = FALSE;
	}
	all->ray[strip_id].ray_angle = ray_angle;
	all->ray[strip_id].ray_down = all->intsc.is_ray_fac_down;
	all->ray[strip_id].ray_up = all->intsc.is_ray_fac_up;
	all->ray[strip_id].ray_left = all->intsc.is_ray_fac_left;
	all->ray[strip_id].ray_right = all->intsc.is_ray_fac_right;
}

void		cast_ray(float ray_angle, int strip_id, t_all *all)
{
	ray_angle = normalize_angle(ray_angle);
	all->intsc.is_ray_fac_down = ray_angle > 0 && ray_angle < PI;
	all->intsc.is_ray_fac_up = !all->intsc.is_ray_fac_down;
	all->intsc.is_ray_fac_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	all->intsc.is_ray_fac_left = !all->intsc.is_ray_fac_right;
	horizontal_intersections(all, ray_angle);
	vertical_intersections(all, ray_angle);
	verify_lower_intersection(all, ray_angle, strip_id);
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
