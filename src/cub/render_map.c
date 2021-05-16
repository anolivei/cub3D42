/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:11:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 22:53:06 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
