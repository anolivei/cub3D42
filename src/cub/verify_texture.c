/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 00:48:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 15:23:38 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	aux_verify_text(char *coord, char *error, t_all *all)
{
	int	fd;

	fd = open(coord, O_RDONLY);
	if (fd < 0)
		all->error.msg = ft_strjoin(all->error.msg, (error));
	close (fd);
}

void	verify_texture(t_data *data, t_all *all)
{
	aux_verify_text(data->NO, "Error\nNorth texture not found\n", all);
	aux_verify_text(data->SO, "Error\nSouth texture not found\n", all);
	aux_verify_text(data->EA, "Error\nEast texture not found\n", all);
	aux_verify_text(data->WE, "Error\nWest texture not found\n", all);
	aux_verify_text(data->sprite, "Error\nsprite texture not found\n", all);
}
