/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:11:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/01 19:25:02 by anolivei         ###   ########.fr       */
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
			if (all->data.map[i][j] == '1')
				all->map.tile_color = RED;
			else
				all->map.tile_color = WHITE;
			draw_square(all, all->map.tile_x, all->map.tile_y,
				all->data.tile_size);
			j++;
		}
		i++;
	}
}

int	has_colision_at(t_all *all, float x, float y, char c)
{
	int	map_x;
	int	map_y;
	int	ret;

	if (x < 0 || x >= all->data.scr_weig * all->data.tile_size || y < 0
		|| y >= all->data.scr_heig * all->data.tile_size)
		return (true);
	map_x = x / all->data.tile_size;
	map_y = y / all->data.tile_size;
	if (all->data.map[map_y][map_x] == c)
		ret = true;
	else
		ret = false;
	return (ret);
}
