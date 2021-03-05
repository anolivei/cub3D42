/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 23:02:15 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/05 00:32:04 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_player(t_all *all)
{
	draw_square(all, all->player.x, all->player.y, all->player.height, MAGENTA);
	draw_line(all, 40);
}