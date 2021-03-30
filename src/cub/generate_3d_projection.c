/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_3d_projection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 00:25:44 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/29 22:10:27 by anolivei         ###   ########.fr       */
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
	//int		color;
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
			put_pixel(&all->img, i, y, YELLOW);
			y++;
		}
		//wall
		if (all->ray[i].hit_vert)
			text_offset_x = (int)all->ray[i].wall_hit_y % TEXT_HEIGHT;
		else
			text_offset_x = (int)all->ray[i].wall_hit_x % TEXT_WIDTH;
		y = wall_top_pixel;
		while (y < wall_bottom_pixel)
		{
			dist_from_top = y + (wall_strip_height / 2) - (WIN_HEIGHT / 2);
			text_offset_y = dist_from_top * ((float)TEXT_HEIGHT / wall_strip_height);
			put_pixel(&all->img, i, y, BLUE);
			y++;
		}
		//floor
		while (y < WIN_HEIGHT)
		{
			put_pixel(&all->img, i, y, GREEN);
			y++;
		}
		i++;
	}
}