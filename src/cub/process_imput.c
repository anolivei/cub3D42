/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_imput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 23:06:00 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/06 02:22:53 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	process_imput(int keycode, t_all *all)
{
	if (keycode == TAB_KEYM || keycode == TAB_KEYL)
		render(all);
	if (keycode == W_KEYM || keycode == W_KEYL)
		walk_turn_dir(all->player.walk_dir, +1, all);
	if (keycode == S_KEYM || keycode == S_KEYL)
		walk_turn_dir(all->player.walk_dir, -1, all);
	if (keycode == D_KEYM || keycode == D_KEYL)
		walk_turn_dir(all->player.turn_dir, +1, all);
	if (keycode == A_KEYM || keycode == A_KEYL)
		walk_turn_dir(all->player.turn_dir, -1, all);
	if (keycode == ESC_KEYM || keycode == ESC_KEYL)
	{
		destroy_window(all);
		return (FALSE);
	}
	return (TRUE);
}

void	walk_turn_dir(int walk_turn_dir, int i, t_all *all)
{
	walk_turn_dir = i;
	render(all);
}

void	destroy_window(t_all *all)
{
		mlx_clear_window(all->mlx.init, all->mlx.window);
		mlx_destroy_window(all->mlx.init, all->mlx.window);
		exit(0);
}