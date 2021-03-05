/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/04 23:38:43 by anolivei         ###   ########.fr       */
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
	return (TRUE);
}

int		destroy_window(int keycode, t_all *all)
{
	if (keycode == D_KEYM || keycode == D_KEYL)
	{
	//	update(&all->player);
	//	all->player.x++;
		render(all);
	}
	
	if (keycode == ESC_KEYM || keycode == ESC_KEYL)
	{
		mlx_clear_window(all->mlx.init, all->mlx.window);
		mlx_destroy_window(all->mlx.init, all->mlx.window);
		exit(0);
		return (FALSE);
	}
	return (TRUE);
}

void	setup(t_player *player)
{
	player->x = WIN_WIDTH / 2;
	player->y = WIN_HEIGHT / 2;
	player->width = 5;
	player->height = 5;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->rot_angle = PI / 2;
	player->walk_speed = 100;
	player->turn_speed = 45 * (PI / 180);
}

void	update(t_player *player)
{
	player->x += 1;
	player->y += 1;
}

void	render(t_all *all)
{
	render_map(all);
//	render_rays();
	render_player(all);

}

int		main(void)
{
	t_all	all;

	initialize_window(&all);
	setup(&all.player);
	update(&all.player);
	mlx_hook(all.mlx.window, 2, 1, destroy_window, &all);
	mlx_loop(all.mlx.init);
	render(&all);
	return (0);
}