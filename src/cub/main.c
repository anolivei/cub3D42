/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/28 23:34:30 by anolivei         ###   ########.fr       */
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
		WIN_WIDTH, WIN_HEIGHT)) == 0)
	{
		ft_putstr_fd("Error initializing new image\n", 1);
		return (FALSE);
	}
	return (TRUE);
}

int		destroy_window(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEYM || keycode == ESC_KEYL)
	{
		mlx_clear_window(mlx->init, mlx->window);
		mlx_destroy_window(mlx->init, mlx->window);
		exit(0);
		return (FALSE);
	}
	return (TRUE);
}

void	setup(t_player *player)
{
	player->x = 0;
	player->y = 0;
}

void	update(t_player *player)
{
	player->x += 1;
	player->y += 1;
}

void	render(void)
{

}

int		main(void)
{
	t_all	all;

	initialize_window(&all);
	setup(&all.player);
	while (1)
	{
		draw_square(&all);
		mlx_hook(all.mlx.window, 2, 1, destroy_window, &all.mlx);
		mlx_loop(all.mlx.init);
		update(&all.player);
		//render();
	}
	return (0);
}
