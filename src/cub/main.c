/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/26 01:58:00 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int initialize_window(t_mlx *mlx)
{
	if ((mlx->init = mlx_init()) == 0)
	{
		ft_putstr_fd("Error initializing minilibX\n", 1);
		return (FALSE);
	}
	if ((mlx->window = mlx_new_window(mlx->init, 1080, 720, "anolivei")) == 0)
	{
		ft_putstr_fd("Error initializing window\n", 1);
		return (FALSE);
	}
	if ((mlx->image = mlx_new_image(mlx->init, 500, 500)) == 0)
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
	t_all		all;

	initialize_window(&all.mlx);
	setup(&all.player);
	while (1)
	{
		mlx_hook(all.mlx.window, 2, 1, destroy_window, &all.mlx);
		mlx_loop(all.mlx.init);
		update(&all.player);
		//render();
	}
	return(0);
}