/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 23:25:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/08 03:08:39 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

const int map3 [MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 1},
	{1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

static void	find_sprites_on_map(t_all *all)
{
	int	i;
	int	j;
	int num;

	i = 0;
	num = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			all->map.tile_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			all->map.tile_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			if (map3[i][j] == 2)
			{
				all->sprite[num].x = all->map.tile_x;
				all->sprite[num].y = all->map.tile_y;
				num++;
			}
			j++;
		}
		i++;
	}
}

void	render_sprites_map(t_all *all)
{
	int i;

	//printf("entrou\n");
	i = 0;
	while (i < NUM_SPRITE)
	{
		//printf("entrou2\n");
		all->map.tile_color = all->sprite[i].visible == 1 ? YELLOW : BLACK;
		printf("%d\n", all->map.tile_color);
		draw_square(all, all->sprite[i].x - (TILE_SIZE / 2), all->sprite[i].y - (TILE_SIZE / 2), 20);
		i++;
	}
}

void	render_sprites_projection(t_all *all)
{
	t_sprite	visible_sprite[NUM_SPRITE];
	int			num_visible_sprite;
	int			i;
	float		angle_sprite_player;

	num_visible_sprite = 0;
	i = 0;
	find_sprites_on_map(all);
	while (i < NUM_SPRITE)
	{
		angle_sprite_player = all->player.rot_angle - atan2(all->sprite[i].y - all->player.y,
			all->sprite[i].x - all->player.x);
		if (angle_sprite_player > PI)
			angle_sprite_player -= TWO_PI;
		if (angle_sprite_player < -PI)
			angle_sprite_player += TWO_PI;
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < FOV / 2)
		{
			all->sprite[i].visible = 1;
			visible_sprite[num_visible_sprite] = all->sprite[i];
			num_visible_sprite++;
			printf("%d\n", all->sprite[i].visible);
		}
		else
		{
			all->sprite[i].visible = 0;
			printf("%d\n", all->sprite[i].visible);
		}
		i++;
	}
	printf("\n\n");
}