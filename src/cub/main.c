/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/10 01:32:18 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	initialize_window(t_all *all)
{
	all->mlx.init = mlx_init();
	if (all->mlx.init == 0)
	{
		ft_putstr_fd("Error initializing minilibX\n", 1);
		return (FALSE);
	}
	verify_file(all);
	all->mlx.window = mlx_new_window(all->mlx.init, all->data.scr_weig,
			all->data.scr_heig, "anolivei");
	if (all->mlx.window == 0)
	{
		ft_putstr_fd("Error initializing window\n", 1);
		return (FALSE);
	}
	all->img.img_ptr = mlx_new_image(all->mlx.init, all->data.scr_weig + 1,
			all->data.scr_heig + 1);
	if (all->img.img_ptr == 0)
	{
		ft_putstr_fd("Error initializing new image\n", 1);
		return (FALSE);
	}
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
			&all->img.size_l, &all->img.endian);
	return (TRUE);
}

void	render(t_all *all)
{
	cast_all_rays(all);
	generate_3d_projection(all);
	render_sprites_projection(all);
	render_map(all);
	render_rays(all);
	render_sprites_map(all);
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}

static void verify_texture(t_data *data)
{
	int fd;

	if ((fd = open(data->NO, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nNorth texture not found\n", 1);
		exit (0);
	}
	if ((fd = open(data->SO, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nSouth texture not found\n", 1);
		exit (0);
	}
	if ((fd = open(data->EA, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nEast texture not found\n", 1);
		exit (0);
	}
	if ((fd = open(data->WE, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nWeast texture not found\n", 1);
		exit (0);
	}
	if ((fd = open(data->sprite, O_RDONLY)) < 0)
	{
		ft_putstr_fd("Error\nSprite texture not found\n", 1);
		exit (0);
	}
}

int		verifica_redor(int x, int y, t_data *data)
{
	int		k;
	int		l;
	char	c;

	k = -1;
	l = -1;
	if (x == 0 || y == 0 || x == data->len_x_map || y == data->len_y_map )
	{
		ft_putstr_fd("Error\nMapa aberto\n", 1);
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

void	verifica_mapa(t_data *data)
{
	int x;
	int y;
	int resp;

	x = 0;
	y = 0;
	resp = 0;

	while (x <=  data->len_y_map - 1)
	{
		y = 0;
		while (y <= data->len_x_map -1 )
		{
			if (data->map[x][y] == '0')
				resp += verifica_redor(y, x, data);
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
	verifica_mapa(data);
}

int	main(int argc, char **argv)
{
	t_all	all;

	setup_map(&all);
	read_cub(&all, argv[1], argc, 0);
	allocate_map(&all, 0, 0, 0);
	verify_dup2(&all.data);
	initialize_window(&all);
	setup_texture(&all, &all.text);
	choose_tile_size(&all.data, &all.text);
	setup_player(&all, &all.player);
	all.ray = malloc((all.data.scr_weig + 1) * sizeof(t_ray));
	all.sprite = malloc((all.data.num_sprites + 1) * sizeof(t_sprite));
	find_sprites_on_map(&all);
	render(&all);
	if (argv[2] && ft_memcmp(argv[2], "--save", 6) == 0
		&& ft_strlen(argv[2]) == 6)
		save_image_bmp(&all);
	process_input(&all);
	mlx_loop(all.mlx.init);
	return (0);
}
