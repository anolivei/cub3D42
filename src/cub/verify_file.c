/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:17:39 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/10 22:40:46 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void aux_verify_text(char *coord, char *error)
{
	int fd;

	fd = open(coord, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(error, 1);
		exit (0);
	}
}

void	verify_texture(t_data *data)
{
	aux_verify_text(data->NO, "Error\nNorth texture not found\n");
	aux_verify_text(data->SO, "Error\nNorth texture not found\n");
	aux_verify_text(data->EA, "Error\nNorth texture not found\n");
	aux_verify_text(data->WE, "Error\nNorth texture not found\n");
}

int	verify_around(int x, int y, t_data *data)
{
	int		k;
	int		l;
	char	c;

	k = -1;
	l = -1;
	if (x == 0 || y == 0 || x == data->len_x_map || y == data->len_y_map )
	{
		ft_putstr_fd("Error\nOpen Maze\n", 1);
		exit (0);
	}
	while (k < 2)
	{
		l = -1;
		while (l < 2)
		{
			c = data->map[y + l][x + k];
			if (((c < '0' || c > '2') && c != data->orientation) || c == ' ')
				return (1);
			l++;
		}
		k++;
	}
	return (0);
}

void	verify_map(t_data *data)
{
	int	x;
	int	y;
	int	resp;

	x = 0;
	y = 0;
	resp = 0;
	while (x <=  data->len_y_map - 1)
	{
		y = 0;
		while (y <= data->len_x_map -1 )
		{
			if (data->map[x][y] == '0')
				resp += verify_around(y, x, data);
			y++;
		}
		x++;
	}
	if (resp > 0)
	{
		ft_putstr_fd("Error\nMapa borda aberta/ caracter inválido\n", 1);
		exit (0);
	}
}

void verify_dup2(t_data *data)
{
	if(data->len_y_map == 0 || data->len_x_map == 0)
	{
		ft_putstr_fd("Error\nNone map or invalid order\n", 1);
		exit (0);
	}
	if (data->qtt.floor != 1 || data->qtt.ceil != 1)
	{
		ft_putstr_fd("Error\nFloor duplicated or empty\n", 1);
		exit (0);
	}
	if (data->qtt.no != 1 || data->qtt.so != 1 || data->qtt.we != 1 || data->qtt.ea != 1 || data->qtt.sprite != 1)
	{
		ft_putstr_fd("Error\nTexture duplicated or empty\n", 1);
		exit (0);
	}
	if (data->qtt.orient != 1)
	{
		ft_putstr_fd("Error\nOrientation duplicated or empty\n", 1);
		exit (0);
	}

	if (data->scr_weig <= 0 || data->scr_heig <= 0 || data->qtt.resol != 1)
	{
		ft_putstr_fd("Error\nResolution duplicated, empty or invalid\n", 1);
		exit (0);
	}
	verify_texture(data);
	verify_map(data);
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
