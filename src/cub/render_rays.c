/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 02:16:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/20 19:29:22 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_rays(t_all *all)
{
	int		i;

	i = 0;
	while (i < NUM_RAYS)
	{
		draw_all_rays(all, i);
		i++;
	}
}