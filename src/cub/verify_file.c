/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 21:17:39 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/04 22:18:22 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	verify_file(t_all *all)
{
	max_resolution(all);	
}

void	max_resolution(t_all *all)
{
	int	screen_width = 5000;
	int	screen_height = 5000;

	//mlx_get_screen_size(all->mlx.init, &screen_width, &screen_height);
	if (all->data.scr_weig > screen_width)
		all->data.scr_weig = screen_width;
	if (all->data.scr_heig > screen_height)
		all->data.scr_heig = screen_height;
}