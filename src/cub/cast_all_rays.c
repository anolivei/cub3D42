/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:00:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 00:24:57 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	setup_rays(t_intsc *hv)
{
	hv->found_wall_hit = FALSE;
	hv->wall_hit_x = 0;
	hv->wall_hit_y = 0;
	hv->wall_content = 0;
}

static void	put_intsc_on_struct(t_intsc *hv, t_all *all, int tf, int strip_id)
{
	all->ray[strip_id].distance = hv->hit_distance;
	all->ray[strip_id].wall_hit_x = hv->wall_hit_x;
	all->ray[strip_id].wall_hit_y = hv->wall_hit_y;
	all->ray[strip_id].wall_hit_content = hv->wall_content;
	all->ray[strip_id].hit_vert = tf;
}

static void	verify_lower_intersection(t_all *all, float ray_angle, int strip_id)
{	
	if (all->hor.found_wall_hit)
		all->hor.hit_distance = distance_between_points(all->player.x,
				all->player.y, all->hor.wall_hit_x, all->hor.wall_hit_y);
	else
		all->hor.hit_distance = FLT_MAX;
	if (all->ver.found_wall_hit)
		all->ver.hit_distance = distance_between_points(all->player.x,
				all->player.y, all->ver.wall_hit_x, all->ver.wall_hit_y);
	else
		all->ver.hit_distance = FLT_MAX;
	if ((all->ver.hit_distance == all->hor.hit_distance)
		&& all->intsc.is_ray_fac_right)
		all->ver.hit_distance--;
	if (all->ver.hit_distance < all->hor.hit_distance)
		put_intsc_on_struct(&all->ver, all, true, strip_id);
	else
		put_intsc_on_struct(&all->hor, all, false, strip_id);
	all->ray[strip_id].ray_angle = ray_angle;
	all->ray[strip_id].ray_down = all->intsc.is_ray_fac_down;
	all->ray[strip_id].ray_up = all->intsc.is_ray_fac_up;
	all->ray[strip_id].ray_left = all->intsc.is_ray_fac_left;
	all->ray[strip_id].ray_right = all->intsc.is_ray_fac_right;
}

void	cast_ray(float ray_angle, int strip_id, t_all *all)
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

void	cast_all_rays(t_all *all)
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
