/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 00:48:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 22:17:49 by anolivei         ###   ########.fr       */
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
	aux_verify_text(data->NO, "North texture not found\n", all);
	aux_verify_text(data->SO, "South texture not found\n", all);
	aux_verify_text(data->EA, "East texture not found\n", all);
	aux_verify_text(data->WE, "West texture not found\n", all);
	aux_verify_text(data->sprite, "Sprite texture not found\n", all);
}
