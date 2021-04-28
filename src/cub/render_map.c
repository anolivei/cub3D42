/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:11:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/27 22:19:50 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_map(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < all->data.len_y_map)
	{
		j = 0;
		while (j < all->data.len_x_map)
		{
			all->map.tile_x = j * all->data.tile_size;
			all->map.tile_y = i * all->data.tile_size;
			all->map.tile_color = all->data.map[i][j] == '1' ? RED : WHITE;
			draw_square(all, all->map.tile_x, all->map.tile_y, all->data.tile_size);
			j++;
		}
		i++;
	}
}

int		has_wall_at(t_all *all, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= all->data.scr_weig * all->data.tile_size || y < 0 || y >= all->data.scr_heig * all->data.tile_size)
		return (TRUE);
	map_x = x / all->data.tile_size;
	map_y = y / all->data.tile_size;
	return (all->data.map[map_y][map_x] == '1' ? 1 : 0);
}

int		has_sprite_at(t_all *all, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= all->data.scr_weig * all->data.tile_size || y < 0 || y >= all->data.scr_heig * all->data.tile_size)
		return (TRUE);
	map_x = x / all->data.tile_size;
	map_y = y / all->data.tile_size;
	return (all->data.map[map_y][map_x] == '2' ? 1 : 0);
}
