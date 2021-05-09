/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 00:25:44 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/08 23:50:21 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	sky(t_all *all, t_proj *p)
{
	p->y = 0;
	while (p->y < ((2 * p->top_pixel) / 2))
	{
		put_pixel(&all->img, p->i, p->y, all->data.ceil);
		p->y++;
	}
}

static void	wall(t_all *all, t_proj *p, int str_heig)
{
	if (all->ray[p->i].hit_vert)
		p->tex_off_x = (int)all->ray[p->i].wall_hit_y % all->data.tile_size;
	else
		p->tex_off_x = (int)all->ray[p->i].wall_hit_x % all->data.tile_size;
	p->tex_off_x *= all->text.north.width / all->data.tile_size;
	p->y = p->top_pixel;
	if (all->ray[p->i].ray_up && !all->ray[p->i].hit_vert)
		all->text.now = all->text.north;
	else if (all->ray[p->i].ray_down && !all->ray[p->i].hit_vert)
		all->text.now = all->text.south;
	else if (all->ray[p->i].ray_right && all->ray[p->i].hit_vert)
		all->text.now = all->text.east;
	else if (all->ray[p->i].ray_left && all->ray[p->i].hit_vert)
		all->text.now = all->text.west;
	while (p->y < p->bottom_pixel)
	{
		p->dist_from_top = p->y + (str_heig / 2) - (all->data.scr_heig / 2);
		p->tex_off_y = p->dist_from_top * ((float)all->text.north.height
				/ str_heig);
		p->color = pick_pixel(&all->text.now, p->tex_off_x, p->tex_off_y);
		put_pixel(&all->img, p->i, p->y, p->color);
		p->y++;
	}
}

static void	ground(t_all *all, t_proj *p)
{
	while (p->y < all->data.scr_heig)
	{
		put_pixel(&all->img, p->i, p->y, all->data.floor);
		p->y++;
	}
}

void	generate_3d_projection(t_all *all)
{
	t_proj	p;
	int		wall_strip_height;
	int		num_rays;

	num_rays = all->data.scr_weig;
	p.i = 0;
	while (p.i < num_rays)
	{
		p.perp_dist = all->ray[p.i].distance * cos(all->ray[p.i].ray_angle
				- all->player.rot_angle);
		p.dist_proj_plane = (all->data.scr_weig / 2) / tan(FOV / 2);
		p.height = (all->data.tile_size / p.perp_dist) * p.dist_proj_plane;
		wall_strip_height = (int)p.height;
		p.top_pixel = (all->data.scr_heig / 2) - (wall_strip_height / 2);
		if (p.top_pixel < 0)
			p.top_pixel = 0;
		p.bottom_pixel = (all->data.scr_heig / 2) + (wall_strip_height / 2);
		if (p.bottom_pixel > all->data.scr_heig)
			p.bottom_pixel = all->data.scr_heig;
		sky(all, &p);
		wall(all, &p, wall_strip_height);
		ground(all, &p);
		p.i++;
	}
}
