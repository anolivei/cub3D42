/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:17:39 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/14 23:35:59 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	verify_around(int x, int y, t_data *data, t_all *all)
{
	int		k;
	int		l;
	char	c;

	k = -1;
	l = -1;
	if (x == 0 || y == 0 || x == data->len_x_map || y == data->len_y_map)
		all->error.msg = "Error\nOpen Maze\n";
	else
	{
		while (k < 2)
		{
			l = -1;
			while (l < 2)
			{
				c = data->map[y + l][x + k];
				if (((c < '0' || c > '2') && c != data->orientation)
					|| c == ' ')
					return (1);
				l++;
			}
			k++;
		}
	}
	return (0);
}

void	verify_map(t_data *data, t_all *all)
{
	int	x;
	int	y;
	int	resp;

	x = 0;
	y = 0;
	resp = 0;
	while (x <= data->len_y_map - 1)
	{
		y = 0;
		while (y <= data->len_x_map -1)
		{
			if (data->map[x][y] == '0')
				resp += verify_around(y, x, data, all);
			y++;
		}
		x++;
	}
	if (resp > 0)
		all->error.msg = "Error\nBorder map5 opened / Invalid character on map\n";
}

void	verify_dup(t_all *all, t_data *data)
{
	if (data->len_y_map == 0 || data->len_x_map == 0)
		all->error.msg = "Error\nWithout map or Invalid order\n";
	if (all->error.floor != 1 || all->error.ceil != 1)
		all->error.msg = "Error\nDuplicate or empty floor\n";
	if (all->error.no != 1 || all->error.so != 1 || all->error.we != 1
		|| all->error.ea != 1 || all->error.sprite != 1)
		all->error.msg = "Error\nDuplicate or empty texture\n";
	if (all->error.orient != 1)
		all->error.msg = "Error\nDuplicate or empty orientation\n";
	if (data->scr_weig <= 0 || data->scr_heig <= 0 || all->error.resol != 1)
		all->error.msg = "Error\nDuplicate, empty or invalid resolution\n";
	verify_texture(data, all);
	verify_map(data, all);
}

void	max_resolution(t_all *all)
{
	int	screen_width;
	int	screen_height;

	screen_width = 5000;
	screen_height = 5000;
//	mlx_get_screen_size(all->mlx.init, &screen_width, &screen_height);
	if (all->data.scr_weig > screen_width)
		all->data.scr_weig = screen_width;
	if (all->data.scr_heig > screen_height)
		all->data.scr_heig = screen_height;
}
