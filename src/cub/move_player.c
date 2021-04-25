/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:59:52 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/24 21:53:51 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	move_player(t_all *all, t_player *player)
{
	float	move_step;
	float	side_step;
	float	new_player_x;
	float	new_player_y;

	player->rot_angle += player->turn_dir * player->turn_speed;
	player->rot_angle = normalize_angle(player->rot_angle);
	move_step = player->walk_dir * player->walk_speed;
	side_step = player->walk_dir_side * player->walk_speed;
	new_player_x = player->x + cos(player->rot_angle) * move_step;
	new_player_y = player->y + sin(player->rot_angle) * move_step;
	if (!has_wall_at(all, new_player_x, new_player_y) && !has_sprite_at(all, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
	new_player_x = player->x + cos(player->rot_angle + 0.5 * PI) * side_step;
	new_player_y = player->y + sin(player->rot_angle + 0.5 * PI) * side_step;
	if (!has_wall_at(all, new_player_x, new_player_y) && !has_sprite_at(all, new_player_x, new_player_y))
	{
		player->x = new_player_x;
		player->y = new_player_y;
	}
}
