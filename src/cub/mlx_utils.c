/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 01:46:59 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/30 23:19:27 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	put_pixel(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_l + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		pick_pixel(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->size_l + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}
