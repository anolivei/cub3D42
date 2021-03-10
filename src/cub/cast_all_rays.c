/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:00:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/10 01:08:41 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float		normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}
static void	setup_hor_rays(t_ray *ray)
{
	
}

void		cast_ray(float ray_angle, int strip_id, t_all *all)
{
	ray_angle = normalize_angle(ray_angle);
	all->ray->is_ray_fac_down = ray_angle > 0 && ray_angle < PI;
	all->ray->is_ray_fac_up = !all->ray->is_ray_fac_down;
	all->ray->is_ray_fac_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	all->ray->is_ray_fac_left = !all->ray->is_ray_fac_right;
	/*
	** Horizontal
	*/
	setup_hor_rays(all->ray);


	
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