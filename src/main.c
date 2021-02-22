/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 00:54:06 by anolivei          #+#    #+#             */
/*   Updated: 2021/02/22 00:38:07 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int initialize_window(t_mlx *mlx)
{
    mlx->init = mlx_init();
    mlx->window = mlx_new_window(mlx->init, 1080, 720, "anolivei");
   // mlx_loop(mlx->window);
    return (0);
}

int destroy_window(int keycode, t_mlx *mlx)
{
	if (keycode == ESC_KEYM || keycode == ESC_KEYL)
	{
		mlx_clear_window(mlx->init, mlx->window);
		mlx_destroy_window(mlx->init, mlx->window);
		exit(0);
		return (1);
	}
    return (0);
}

int main(void)
{
    t_mlx mlx;

    initialize_window(&mlx);
//    setup();
//    while (1)
//    {
       //processImput();
       //update();
       //render();
//    }all.mlx = mlx;
	mlx_hook(mlx.window, 2, 1, destroy_window, &mlx);
	mlx_loop(mlx.init);
    return(0);
}