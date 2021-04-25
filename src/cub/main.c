/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/25 01:36:12 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int		initialize_window(t_all *all)
{
	if ((all->mlx.init = mlx_init()) == 0)
	{
		ft_putstr_fd("Error initializing minilibX\n", 1);
		return (FALSE);
	}
	if ((all->mlx.window = mlx_new_window(all->mlx.init, all->data.scr_weig, all->data.scr_heig,
		"anolivei")) == 0)
	{
		ft_putstr_fd("Error initializing window\n", 1);
		return (FALSE);
	}
	if ((all->img.img_ptr = mlx_new_image(all->mlx.init,
		all->data.scr_weig + 1, all->data.scr_heig + 1)) == 0)
	{
		ft_putstr_fd("Error initializing new image\n", 1);
		return (FALSE);
	}
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	return (TRUE);
}

void	setup_player(t_all *all, t_player *player)
{
	player->width = 1;
	player->height = 1;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->walk_dir_side = 0;
	if (all->data.orientation == 'W')
		player->rot_angle = PI;
	else if (all->data.orientation == 'E')
		player->rot_angle = 0;
	else if (all->data.orientation == 'N')
		player->rot_angle = 1.5 * PI;
	else if (all->data.orientation == 'S')
		player->rot_angle = 0.5 * PI;
	player->walk_speed = 20;
	player->turn_speed = 10 * (PI / 180);
}

void	setup_map(t_all *all)
{
	all->data.map_line = ft_strdup("");
	all->data.len_x_map = 0;
	all->data.len_y_map = 0;
	all->data.num_sprites = 0;
}

void	setup_texture(t_all *all, t_text *text)
{
	text->north.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
		all->data.NO, &text->north.width, &text->north.height);
	text->north.addr = mlx_get_data_addr(text->north.img_ptr,
		&text->north.bpp, &text->north.size_l, &text->north.endian);

	text->south.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
		all->data.SO, &text->south.width, &text->south.height);
	text->south.addr = mlx_get_data_addr(text->south.img_ptr,
		&text->south.bpp, &text->south.size_l, &text->south.endian);

	text->east.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
		all->data.EA, &text->east.width, &text->east.height);
	text->east.addr = mlx_get_data_addr(text->east.img_ptr,
		&text->east.bpp, &text->east.size_l, &text->east.endian);

	text->west.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
		all->data.WE, &text->west.width, &text->west.height);
	text->west.addr = mlx_get_data_addr(text->west.img_ptr,
		&text->west.bpp, &text->west.size_l, &text->west.endian);

	text->sprite.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
		all->data.sprite, &text->sprite.width, &text->sprite.height);
	text->sprite.addr = mlx_get_data_addr(text->sprite.img_ptr,
		&text->sprite.bpp, &text->sprite.size_l, &text->sprite.endian);
}

void	render(t_all *all)
{
	cast_all_rays(all);
	generate_3d_projection(all);
	render_sprites_projection(all);
	render_map(all);
	render_rays(all);
	render_sprites_map(all);
	render_player(all);
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}

int		main(int argc, char **argv)
{
	t_all	all;
	
	setup_map(&all);
	read_cub(&all, argv[1], argc);
	allocate_map(&all, 0, 0, 0);
	initialize_window(&all);
	setup_texture(&all, &all.text);
	setup_player(&all, &all.player);
	render(&all);
	process_input(&all);
	mlx_loop(all.mlx.init);
	return (0);
}
