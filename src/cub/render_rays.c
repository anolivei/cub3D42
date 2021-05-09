/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:16:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/04 21:56:29 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_rays(t_all *all)
{
	int	i;
	int	num_rays;

	num_rays = all->data.scr_weig;
	i = 0;
	while (i < num_rays)
	{
		draw_all_rays(all, i);
		i++;
	}
}
