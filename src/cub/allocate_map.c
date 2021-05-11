/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 17:45:10 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/10 22:46:19 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	count_sprites(t_data *data, int p, int i, int j)
{
	if (data->map_line[p] == '2')
	{
		if (i == 0 || j == 0 || i == data->len_y_map - 1 || j == data->len_x_map - 1)
		{
			ft_putstr_fd("Error\nInvalid map, sprites on border\n", 1);
			exit (0);
		}
		data->num_sprites++;
	}


}

void	ft_bzero(void *s, size_t n)
{
	unsigned char *str;

	if (n != 0)
	{
		str = (unsigned char *)s;
		s = ft_memset(s, 0, n);
	}
}

void	allocate_map(t_all *all, int i, int j, int p)
{
	all->data.map = malloc((all->data.len_y_map + 1) * sizeof(char *) + 1);
	all->data.map[0] = malloc((all->data.len_x_map + 1) * sizeof(char *) + 1);
	ft_bzero(all->data.map[0],all->data.len_x_map+1);
	while (all->data.map_line[p] != '\0')
	{
		if (all->data.map_line[p] == '\n')
		{
			i++;
			j = 0;
			all->data.map[i] = malloc(all->data.len_x_map * sizeof(char *) + 1);
			ft_bzero(all->data.map[i],all->data.len_x_map+1);
		}
		else
		{
			all->data.map[i][j] = all->data.map_line[p];
			if (all->data.map_line[p] == 'N' || all->data.map_line[p] == 'S'
				|| all->data.map_line[p] == 'W' || all->data.map_line[p] == 'E')
			{
				if (i == 0 || j == 0 || i == all->data.len_y_map  || j == all->data.len_x_map)
				{
					ft_putstr_fd("Error\nInvalid map, orientation on border\n", 1);
					exit(0);
				}
			//	printf("ori%d %d\n",i,j);
				all->data.qtt.orient++;
				all->player.x = j;
				all->player.y = i;
				all->data.orientation = all->data.map_line[p];
			}
			count_sprites(&all->data, p, i, j);
			j++;
		}
		p++;
	}
}
