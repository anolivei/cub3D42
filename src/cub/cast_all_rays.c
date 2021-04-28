/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:00:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/27 22:25:25 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	setup_rays(t_intsc *hv)
{
	hv->found_wall_hit = FALSE;
	hv->wall_hit_x = 0;
	hv->wall_hit_y = 0;
	hv->wall_content = 0;
}

static void	horizontal_intersections(t_all *all, float ray_angle)
{
	int max_width;
	int max_height;
	
	setup_rays(&all->hor);
	all->hor.y_interc = floor (all->player.y / all->data.tile_size) * all->data.tile_size;
	all->hor.y_interc += all->intsc.is_ray_fac_down ? all->data.tile_size : 0;
	all->hor.x_interc = all->player.x + (all->hor.y_interc - all->player.y) / tan(ray_angle);
	all->hor.y_step = all->data.tile_size;
	all->hor.y_step *= all->intsc.is_ray_fac_up ? -1 : 1;
	all->hor.x_step = all->data.tile_size / tan(ray_angle);
	all->hor.x_step *= (all->intsc.is_ray_fac_left && all->hor.x_step > 0) ? -1 : 1;
	all->hor.x_step *= (all->intsc.is_ray_fac_right && all->hor.x_step < 0) ? -1 : 1;
	max_width = all->data.tile_size * all->data.len_x_map;
	max_height = all->data.tile_size * all->data.len_y_map;
	all->hor.next_touch_x = all->hor.x_interc;
	all->hor.next_touch_y = all->hor.y_interc;
	while (all->hor.next_touch_x >= 0 && all->hor.next_touch_x <= max_width &&
		all->hor.next_touch_y >= 0 && all->hor.next_touch_y <= max_height)
	{
		all->hor.x_to_check = all->hor.next_touch_x;
		if (all->intsc.is_ray_fac_up)
			all->hor.y_to_check = all->hor.next_touch_y - 1;
		else
			all->hor.y_to_check = all->hor.next_touch_y;
		if (has_wall_at(all, all->hor.x_to_check, all->hor.y_to_check))
		{
			all->hor.wall_hit_x = all->hor.next_touch_x;
			all->hor.wall_hit_y = all->hor.next_touch_y;
			all->hor.wall_content = all->data.map[(int)floor(all->hor.y_to_check / all->data.tile_size)]
				[(int)floor(all->hor.x_to_check / all->data.tile_size)];
			all->hor.found_wall_hit = TRUE;
			break;
		}
		all->hor.next_touch_x += all->hor.x_step;
		all->hor.next_touch_y += all->hor.y_step;
	}
}

static void	vertical_intersections(t_all *all, float ray_angle)
{
	int max_width;
	int max_height;
	
	setup_rays(&all->ver);
	all->ver.x_interc = floor(all->player.x / all->data.tile_size) * all->data.tile_size;
	all->ver.x_interc += all->intsc.is_ray_fac_right ? all->data.tile_size : 0;
	all->ver.y_interc = all->player.y + (all->ver.x_interc - all->player.x) * tan(ray_angle);
	all->ver.x_step = all->data.tile_size;
	all->ver.x_step *= all->intsc.is_ray_fac_left ? -1 : 1;
	all->ver.y_step = all->data.tile_size * tan(ray_angle);
	all->ver.y_step *= (all->intsc.is_ray_fac_up && all->ver.y_step > 0) ? -1 : 1;
	all->ver.y_step *= (all->intsc.is_ray_fac_down && all->ver.y_step < 0) ? -1 : 1;
	all->ver.next_touch_x = all->ver.x_interc;
	all->ver.next_touch_y = all->ver.y_interc;
	max_width = all->data.tile_size * all->data.len_x_map - 1;
	max_height = all->data.tile_size * all->data.len_y_map - 1;
	while (all->ver.next_touch_x >= 0 && all->ver.next_touch_x <= max_width &&
		all->ver.next_touch_y >= 0 && all->ver.next_touch_y <= max_height)
	{
		all->ver.y_to_check = all->ver.next_touch_y;
		if (all->intsc.is_ray_fac_left)
			all->ver.x_to_check = all->ver.next_touch_x - 1;
		else
			all->ver.x_to_check = all->ver.next_touch_x;
		if (has_wall_at(all, all->ver.x_to_check, all->ver.y_to_check))
		{
			all->ver.wall_hit_x = all->ver.next_touch_x;
			all->ver.wall_hit_y = all->ver.next_touch_y;
			all->ver.wall_content = all->data.map[(int)floor(all->ver.y_to_check / all->data.tile_size)]
				[(int)floor(all->ver.x_to_check / all->data.tile_size)];
			all->ver.found_wall_hit = TRUE;
			break ;
		}
		all->ver.next_touch_x += all->ver.x_step;
		all->ver.next_touch_y += all->ver.y_step;
	}
}

static void	verify_lower_intersection(t_all *all, float ray_angle, int strip_id)
{	
	all->hor.hit_distance = all->hor.found_wall_hit
		? distance_between_points(all->player.x, all->player.y, all->hor.wall_hit_x, all->hor.wall_hit_y) : FLT_MAX;
	all->ver.hit_distance = all->ver.found_wall_hit
		? distance_between_points(all->player.x, all->player.y, all->ver.wall_hit_x, all->ver.wall_hit_y) : FLT_MAX;
	if ((all->ver.hit_distance == all->hor.hit_distance) && all->intsc.is_ray_fac_right)
		all->ver.hit_distance--;
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
	int		num_rays;

	all->ray = malloc((all->data.scr_weig + 1) * sizeof(t_ray));
	num_rays = all->data.scr_weig;
	ray_angle = all->player.rot_angle - (FOV / 2);
	strip_id = 0;
	while (strip_id < num_rays)
	{
		cast_ray(ray_angle, strip_id, all);
		ray_angle += FOV / num_rays;
		strip_id++;
	}
}
