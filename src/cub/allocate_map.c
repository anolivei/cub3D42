/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:45:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 17:40:05 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	count_sprites(t_all *all, int i, int j, int p)
{
	if (all->data.map_line[p] == '2')
	{
		if (i == 0 || j == 0 || i == all->data.len_y_map - 1
			|| j == all->data.len_x_map - 1)
			all->error.msg = ft_strjoin(all->error.msg,
					"\nInvalid map, sprites on border");
		all->data.num_sprites++;
	}
}

static void	verify_orientation(t_all *all, int i, int j, int p)
{
	if (all->data.map_line[p] == 'N' || all->data.map_line[p] == 'S'
		|| all->data.map_line[p] == 'W' || all->data.map_line[p] == 'E')
	{
		if (i == 0 || j == 0 || i == all->data.len_y_map
			|| j == all->data.len_x_map)
			all->error.msg = ft_strjoin(all->error.msg,
					"\nInvalid map, orientation on border");
		all->error.orient++;
		all->player.x = j;
		all->player.y = i;
		all->data.orientation = all->data.map_line[p];
	}
}

void	allocate_map(t_all *all, int i, int j, int p)
{
	all->error.double_map = 0;
	while (all->data.map_line[p] != '\0')
	{
		if (all->data.map_line[p] == '\n')
		{
			if (j == 0)
				all->error.double_map = 99;
			i++;
			j = 0;
		}
		else
		{
			all->data.map[i][j] = all->data.map_line[p];
			verify_orientation(all, i, j, p);
			count_sprites(all, i, j, p);
			j++;
		}
		p++;
	}
}
