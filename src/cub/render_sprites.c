/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 23:25:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/11 01:15:20 by anolivei         ###   ########.fr       */
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
	{1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
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

	i = 0;
	while (i < NUM_SPRITE)
	{
		all->map.tile_color = all->sprite[i].visible == 1 ? YELLOW : BLACK;
		draw_square(all, all->sprite[i].x - (TILE_SIZE / 2), all->sprite[i].y - (TILE_SIZE / 2), 20);
		i++;
	}
}

t_sprite	*sort_sprites(t_sprite *visible_sprite, int num_visible_sprite)
{
	int			i;
	int			j;
	t_sprite	sprite;

	i = 0;
	while (i < num_visible_sprite - 1)
	{
		j = i + 1;
		while (j < num_visible_sprite)
		{
			if (visible_sprite[i].distance < visible_sprite[j].distance)
			{
				sprite = visible_sprite[i];
				visible_sprite[i] = visible_sprite[j];
				visible_sprite[j] = sprite;
			}
			j++;
		}
		i++;
	}
	return(visible_sprite);
}

void	render_visible_sprites(t_all *all, t_sprite *visible_sprite, int num_visible_sprites)
{
	int			i;
	float		dist_proj_plane;
	int			top_pixel;
	int			bottom_pixel;
	int			right_pixel;
	int			left_pixel;
	int			x;
	int			y;
	float		sprite_angle;
	float		sprite_pos_x;
	t_sprite	sprite;
	float		height;
	float		width;
	int			color;
	int			text_offset_x;
	int			text_offset_y;
	float		text_width;
	int			dist_from_top;

	i = 0;
	while(i < num_visible_sprites)
	{
		sprite = visible_sprite[i];
		dist_proj_plane = (WIN_WIDTH / 2) / tan(FOV / 2);

		height = (TILE_SIZE / sprite.distance) * dist_proj_plane;
		width = height;

		top_pixel = (WIN_HEIGHT / 2) - (height / 2);
		top_pixel = top_pixel < 0 ? 0 : top_pixel;

		bottom_pixel = (WIN_HEIGHT / 2) + (height / 2);
		bottom_pixel = bottom_pixel > WIN_HEIGHT ? WIN_HEIGHT : bottom_pixel;

		sprite_angle = atan2(sprite.y - all->player.y, sprite.x - all->player.x) - all->player.rot_angle;

		sprite_pos_x = tan(sprite_angle) * dist_proj_plane;

		left_pixel = (WIN_WIDTH / 2) + sprite_pos_x - (width / 2);

		right_pixel = left_pixel + width;

		x = left_pixel;
		while(x < right_pixel)
		{
			text_width = all->text.sprite.width / width;
			text_offset_x = (x - left_pixel) * text_width;
			y = top_pixel;
			while (y < bottom_pixel)
			{
				dist_from_top = y + (height / 2) - (WIN_HEIGHT / 2);
				text_offset_y = dist_from_top * ((float)all->text.sprite.height / height);
				if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
				{
					color = pick_pixel(&all->text.sprite, text_offset_x, text_offset_y);
					if (sprite.distance < all->ray[x].distance && color > 0)
						put_pixel(&all->img, x, y, color);
				}
				y++;
			}
			x++;
		}
		i++;
	}
}

void	render_sprites_projection(t_all *all)
{
	t_sprite	*visible_sprite;
	int			num_visible_sprite;
	int			i;
	float		angle_sprite_player;

	num_visible_sprite = 0;
	visible_sprite = malloc(sizeof(t_sprite) * NUM_SPRITE);
	i = 0;
	find_sprites_on_map(all);
	while (i < NUM_SPRITE)
	{
		angle_sprite_player = all->player.rot_angle - atan2(all->sprite[i].y - all->player.y,
			all->sprite[i].x - all->player.x);
		angle_sprite_player = normalize_angle(angle_sprite_player);
		if (angle_sprite_player > PI)
			angle_sprite_player -= TWO_PI;
		if (angle_sprite_player < -PI)
			angle_sprite_player += TWO_PI;
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < ((FOV / 2) + 0.3))
		{
			all->sprite[i].visible = 1;
			all->sprite[i].angle = angle_sprite_player;
			all->sprite[i].distance = distance_between_points(all->player.x, all->player.y,  all->sprite[i].x, all->sprite[i].y);
			visible_sprite[num_visible_sprite] = all->sprite[i];
			num_visible_sprite++;
		}
		else
		{
			all->sprite[i].visible = 0;
		}
		i++;
	}
	visible_sprite = sort_sprites(visible_sprite, num_visible_sprite);
	render_visible_sprites(all, visible_sprite, num_visible_sprite);
	free (visible_sprite);
}
