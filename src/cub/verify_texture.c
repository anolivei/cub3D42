/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 00:48:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/11 00:59:47 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	aux_verify_text(char *coord, char *error)
{
	int	fd;

	fd = open(coord, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(error, 1);
		exit (0);
	}
}

void	verify_texture(t_data *data)
{
	aux_verify_text(data->NO, "Error\nNorth texture not found\n");
	aux_verify_text(data->SO, "Error\nSouth texture not found\n");
	aux_verify_text(data->EA, "Error\nEast texture not found\n");
	aux_verify_text(data->WE, "Error\nWest texture not found\n");
}
