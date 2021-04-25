/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:11:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/25 01:08:03 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_map(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			all->map.tile_x = j * TILE_SIZE;
			all->map.tile_y = i * TILE_SIZE;
			all->map.tile_color = all->data.map[i][j] == '1' ? RED : WHITE;
			draw_square(all, all->map.tile_x, all->map.tile_y, TILE_SIZE);
			j++;
		}
		i++;
	}
}

int		has_wall_at(t_all *all, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > all->data.scr_weig || y < 0 || y > all->data.scr_heig)
		return (TRUE);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (all->data.map[map_y][map_x] == '1' ? 1 : 0);
}

int		has_sprite_at(t_all *all, float x, float y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > all->data.scr_weig || y < 0 || y > all->data.scr_heig)
		return (TRUE);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (all->data.map[map_y][map_x] == '2' ? 1 : 0);
}
