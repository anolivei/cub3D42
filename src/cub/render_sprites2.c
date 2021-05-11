/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 02:31:41 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/11 20:45:36 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	find_sprites_on_map(t_all *all)
{
	int	i;
	int	j;
	int	num;

	i = 0;
	num = 0;
	while (i < all->data.len_y_map)
	{
		j = 0;
		while (j < all->data.len_x_map)
		{
			all->map.tile_x = (j * all->data.tile_size)
				+ (all->data.tile_size / 2);
			all->map.tile_y = (i * all->data.tile_size)
				+ (all->data.tile_size / 2);
			if (all->data.map[i][j] == '2')
			{
				all->sprite[num].x = all->map.tile_x;
				all->sprite[num].y = all->map.tile_y;
				num++;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites_map(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data.num_sprites)
	{
		if (all->sprite[i].visible == 1)
			all->map.tile_color = YELLOW;
		else
			all->map.tile_color = BLACK;
		draw_square(all, all->sprite[i].x - (all->data.tile_size / 2),
			all->sprite[i].y - (all->data.tile_size / 2), 20);
		i++;
	}
}

t_sprite	*sort_sprites(t_sprite *visible_sprite, int num_visible_sprite)
{
	int			i;
	int			j;
	t_sprite	sprite;

	i = 0;
	while (i < num_visible_sprite - 1)
	{
		j = i + 1;
		while (j < num_visible_sprite)
		{
			if (visible_sprite[i].distance < visible_sprite[j].distance)
			{
				sprite = visible_sprite[i];
				visible_sprite[i] = visible_sprite[j];
				visible_sprite[j] = sprite;
			}
			j++;
		}
		i++;
	}
	return (visible_sprite);
}
