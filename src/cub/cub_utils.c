/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 01:52:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/21 01:52:52 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float		normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

float		distance_between_points(t_player *player, t_intsc *hv)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = player->x;
	y1 = player->y;
	x2 = hv->wall_hit_x;
	y2 = hv->wall_hit_y;
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
