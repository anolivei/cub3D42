/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:45:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 21:34:41 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	count_sprites(t_data *data, int p)
{
	if (data->map_line[p] == '2')
		data->num_sprites++;
}

void	allocate_map(t_all *all, int i, int j, int p)
{
	all->data.map = malloc((all->data.len_y_map + 1) * sizeof(char *) + 1);
	all->data.map[0] = malloc((all->data.len_x_map + 1) * sizeof(char *) + 1);
	while (all->data.map_line[p] != '\0')
	{
		if (all->data.map_line[p] == '\n')
		{
			i++;
			j = 0;
			all->data.map[i] = malloc(all->data.len_x_map * sizeof(char *) + 1);
		}
		else
		{
			all->data.map[i][j] = all->data.map_line[p];
			if (all->data.map_line[p] == 'N' || all->data.map_line[p] == 'S'
				|| all->data.map_line[p] == 'W' || all->data.map_line[p] == 'E')
			{
				all->player.x = j;
				all->player.y = i;
				all->data.orientation = all->data.map_line[p];
			}
			count_sprites(&all->data, p);
			j++;
		}
		p++;
	}
}
