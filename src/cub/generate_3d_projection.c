/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 00:25:44 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/21 19:37:11 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	generate_3d_projection(t_all *all)
{
	int		i;
	int		y;
	int		wall_strip_height;
	float	dist_proj_plane;
	float	proj_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	float	perp_dist;
	int		color;
	int		text_offset_x;
	int		text_offset_y;
	int		dist_from_top;

	i = 0;
	while(i < NUM_RAYS)
	{
		perp_dist = all->ray[i].distance * cos(all->ray[i].ray_angle - all->player.rot_angle);
		dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
		proj_wall_height = (TILE_SIZE / perp_dist) * dist_proj_plane;
		wall_strip_height = (int)proj_wall_height;
		wall_top_pixel = (WIN_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (WIN_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > WIN_HEIGHT ? WIN_HEIGHT : wall_bottom_pixel;
		//ceil
		y = 0;
		while (y < ((2 * wall_top_pixel) / 2))
		{
			put_pixel(&all->img, i, y, all->data.ceil);
			y++;
		}
		//wall
		if (all->ray[i].hit_vert)
			text_offset_x = (int)all->ray[i].wall_hit_y % all->text.north.height;
		else
			text_offset_x = (int)all->ray[i].wall_hit_x % all->text.north.width;
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			dist_from_top = y + (wall_strip_height / 2) - (WIN_HEIGHT / 2);
			text_offset_y = dist_from_top * ((float)all->text.north.height / wall_strip_height);

			if (all->ray[i].ray_up && !all->ray[i].hit_vert)
				color = pick_pixel(&all->text.north, text_offset_x, text_offset_y);
			else if (all->ray[i].ray_down && !all->ray[i].hit_vert)
				color = pick_pixel(&all->text.south, text_offset_x, text_offset_y);
			else if (all->ray[i].ray_right && all->ray[i].hit_vert)
				color = pick_pixel(&all->text.east, text_offset_x, text_offset_y);
			else if (all->ray[i].ray_left && all->ray[i].hit_vert)
				color = pick_pixel(&all->text.west, text_offset_x, text_offset_y);
		
			put_pixel(&all->img, i, y, color);
			y++;
		}
		//floor
		while (y < WIN_HEIGHT)
		{
			put_pixel(&all->img, i, y, all->data.floor);
			y++;
		}
		i++;
	}
}