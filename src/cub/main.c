/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/16 02:38:35 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	initialize_window(t_all *all)
{
	all->mlx.init = mlx_init();
	if (all->mlx.init == 0)
	{
		all->error.msg = ft_strjoin(all->error.msg, "\nCan't initialize mlx");
		return (FALSE);
	}
	max_resolution(all);
	all->mlx.window = mlx_new_window(all->mlx.init, all->data.scr_weig,
			all->data.scr_heig, "anolivei");
	if (all->mlx.window == 0)
	{
		all->error.msg = ft_strjoin(all->error.msg, "\nCan't initialize window");
		return (FALSE);
	}
	all->img.img_ptr = mlx_new_image(all->mlx.init, all->data.scr_weig + 1,
			all->data.scr_heig + 1);
	if (all->img.img_ptr == 0)
	{
		all->error.msg = ft_strjoin(all->error.msg, "\nCan't initialize image");
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
	if (all->bmp.dont_put_on_screen == 0)
		mlx_put_image_to_window(all->mlx.init, all->mlx.window,
			all->img.img_ptr, 0, 0);
}

int	main(int argc, char **argv)
{
	t_all	all;

	setup_map(&all);
	read_cub(&all, argv[1], argc);
	allocate_map(&all, 0, 0, 0);
	verify_dup(&all, &all.data);
	exit_failure(&all);
	initialize_window(&all);
	setup_texture(&all, &all.text);
	choose_tile_size(&all.data, &all.text);
	setup_player(&all, &all.player);
	all.ray = malloc((all.data.scr_weig + 1) * sizeof(t_ray));
	all.sprite = malloc((all.data.num_sprites + 1) * sizeof(t_sprite));
	all.visible_sprite = malloc(sizeof(t_sprite) * all.data.num_sprites);
	find_sprites_on_map(&all);
	if (argv[2] && ft_memcmp(argv[2], "--save", 6) == 0
		&& ft_strlen(argv[2]) == 6)
		save_image_bmp(&all);
	render(&all);
	process_input(&all);
	mlx_loop(all.mlx.init);
	return (0);
}
