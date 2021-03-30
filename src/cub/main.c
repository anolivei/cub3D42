/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/30 00:22:25 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"
#include "../../includes/textures.h"

int		initialize_window(t_all *all)
{
	if ((all->mlx.init = mlx_init()) == 0)
	{
		ft_putstr_fd("Error initializing minilibX\n", 1);
		return (FALSE);
	}
	if ((all->mlx.window = mlx_new_window(all->mlx.init, WIN_WIDTH, WIN_HEIGHT,
		"anolivei")) == 0)
	{
		ft_putstr_fd("Error initializing window\n", 1);
		return (FALSE);
	}
	if ((all->img.img_ptr = mlx_new_image(all->mlx.init,
		WIN_WIDTH + 1, WIN_HEIGHT + 1)) == 0)
	{
		ft_putstr_fd("Error initializing new image\n", 1);
		return (FALSE);
	}
	all->img.addr = mlx_get_data_addr(all->img.img_ptr, &all->img.bpp,
		&all->img.size_l, &all->img.endian);
	return (TRUE);
}

void	setup_player(t_player *player)
{
	player->x = WIN_WIDTH / 2;
	player->y = WIN_HEIGHT / 2;
	player->width = 1;
	player->height = 1;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rot_angle = 45 * (PI / 180);
	player->walk_speed = 10;
	player->turn_speed = 5 * (PI / 180);
}

void	setup_texture(t_text *text)
{
	text->texture[0] = (int)REDBRICK_TEXTURE;
	text->texture[1] = (int)PURPLESTONE_TEXTURE;
	text->texture[2] = (int)MOSSYSTONE_TEXTURE;
	text->texture[3] = (int)GRAYSTONE_TEXTURE;
	text->texture[4] = (int)COLORSTONE_TEXTURE;
	text->texture[5] = (int)BLUESTONE_TEXTURE;
	text->texture[6] = (int)WOOD_TEXTURE;
	text->texture[7] = (int)EAGLE_TEXTURE;
}

void	render(t_all *all)
{
	cast_all_rays(all);
	generate_3d_projection(all);
	render_map(all);
	render_rays(all);
	render_player(all);
	mlx_put_image_to_window(all->mlx.init, all->mlx.window,
		all->img.img_ptr, 0, 0);
}

int		main(void)
{
	t_all	all;

	initialize_window(&all);
	setup_player(&all.player);
	setup_texture(&all.text);
	render(&all);
	process_input(&all);
	mlx_loop(all.mlx.init);
	return (0);
}
