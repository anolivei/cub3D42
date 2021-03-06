/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:06:00 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/05 23:41:10 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	process_imput(int keycode, t_all *all)
{
	if (keycode == TAB_KEYM || keycode == TAB_KEYL)
		render(all);
	if (keycode == W_KEYM || keycode == W_KEYL)
	{
		all->player.y--;
		render(all);
	}
	if (keycode == S_KEYM || keycode == S_KEYL)
	{
		all->player.y++;
		render(all);
	}
	if (keycode == A_KEYM || keycode == A_KEYL)
	{
		all->player.x--;
		render(all);
	}
	if (keycode == D_KEYM || keycode == D_KEYL)
	{
		all->player.x++;
		render(all);
	}
/*	if (keycode == LEFT_ARROW_KEYM || keycode == LEFT_ARROW_KEYL)
	{

	}
	if (keycode == W_KEYM || keycode == W_KEYL)
	{

	}*/
	if (keycode == ESC_KEYM || keycode == ESC_KEYL)
	{
		destroy_window(all);
		return (FALSE);
	}
	return (TRUE);
}

void	destroy_window(t_all *all)
{
		mlx_clear_window(all->mlx.init, all->mlx.window);
		mlx_destroy_window(all->mlx.init, all->mlx.window);
		exit(0);
}