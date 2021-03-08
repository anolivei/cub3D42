/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:59:52 by anolivei          #+#    #+#             */
/*   Updated: 2021/03/07 21:22:26 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	move_player(t_player *player)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	player->rot_angle += player->turn_dir * player->turn_speed;
	move_step = player->walk_dir * player->walk_speed;
	new_player_x = player->x + cos(player->rot_angle) * move_step;
	new_player_y = player->y + sin(player->rot_angle) * move_step;
	player->x = new_player_x;
	player->y = new_player_y;
}