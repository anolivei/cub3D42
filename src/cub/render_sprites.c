/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 23:25:05 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/16 00:17:00 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	render_vis_spr2(t_all *all, t_sprite *sprite, t_proj *p)
{
	float	text_width;

	while (p->x < p->right_pixel)
	{
		text_width = all->text.sprite.width / p->width;
		p->tex_off_x = (p->x - p->left_pixel) * text_width;
		p->y = p->top_pixel;
		while (p->y < p->bottom_pixel)
		{
			p->dist_from_top = p->y + (p->height / 2)
				- (all->data.scr_heig / 2);
			p->tex_off_y = p->dist_from_top * ((float)all->text.sprite.height
					/ p->height);
			if (p->x > 0 && p->x < all->data.scr_weig && p->y > 0 && p->y
				< all->data.scr_heig)
			{
				p->color = pick_pixel(&all->text.sprite, p->tex_off_x,
						p->tex_off_y);
				if (sprite->distance < all->ray[p->x].distance && p->color > 0)
					put_pixel(&all->img, p->x, p->y, p->color);
			}
			p->y++;
		}
		p->x++;
	}
}

void	render_vis_spr(t_all *all, t_sprite *vis_spr, int num_vis_spr)
{
	t_proj		p;
	t_sprite	sprite;

	p.i = -1;
	while (++p.i < num_vis_spr)
	{
		sprite = vis_spr[p.i];
		p.perp_dist = sprite.distance * cos(sprite.angle);
		p.dist_proj_plane = (all->data.scr_weig / 2) / tan(FOV / 2);
		p.height = (all->data.tile_size / p.perp_dist) * p.dist_proj_plane;
		p.width = p.height;
		p.top_pixel = (all->data.scr_heig / 2) - (p.height / 2);
		if (p.top_pixel < 0)
			p.top_pixel = 0;
		p.bottom_pixel = (all->data.scr_heig / 2) + (p.height / 2);
		if (p.bottom_pixel > all->data.scr_heig)
			p.bottom_pixel = all->data.scr_heig;
		p.spr_angle = atan2(sprite.y - all->player.y, sprite.x
				- all->player.x) - all->player.rot_angle;
		p.spr_pos_x = tan(p.spr_angle) * p.dist_proj_plane;
		p.left_pixel = (all->data.scr_weig / 2) + p.spr_pos_x - (p.width / 2);
		p.right_pixel = p.left_pixel + p.width;
		p.x = p.left_pixel;
		render_vis_spr2(all, &sprite, &p);
	}
}

static float	normalize_sprite_angle(float angle_sprite_player)
{
	if (angle_sprite_player > PI)
		angle_sprite_player -= TWO_PI;
	if (angle_sprite_player < -PI)
		angle_sprite_player += TWO_PI;
	return (angle_sprite_player);
}

static int	calc_num_vis_sprites(t_all *all, float angle_sprite_player,
		t_sprite *visible_sprite, int num_visible_sprite)
{
	int	i;

	i = 0;
	while (i < all->data.num_sprites)
	{
		angle_sprite_player = all->player.rot_angle - atan2(all->sprite[i].y
				- all->player.y, all->sprite[i].x - all->player.x);
		angle_sprite_player = normalize_angle(angle_sprite_player);
		angle_sprite_player = normalize_sprite_angle(angle_sprite_player);
		angle_sprite_player = fabs(angle_sprite_player);
		if (angle_sprite_player < ((FOV / 2) + 0.3))
		{
			all->sprite[i].visible = 1;
			all->sprite[i].angle = angle_sprite_player;
			all->sprite[i].distance = distance_between_points(all->player.x,
					all->player.y, all->sprite[i].x, all->sprite[i].y);
			visible_sprite[num_visible_sprite] = all->sprite[i];
			num_visible_sprite++;
		}
		else
			all->sprite[i].visible = 0;
		i++;
	}
	return (num_visible_sprite);
}

void	render_sprites_projection(t_all *all)
{
	int			num_visible_sprite;

	num_visible_sprite = 0;
	ft_bzero(all->visible_sprite, all->data.num_sprites);
	find_sprites_on_map(all);
	num_visible_sprite = calc_num_vis_sprites(all, 0, all->visible_sprite, 0);
	all->visible_sprite = sort_sprites(all->visible_sprite, num_visible_sprite);
	render_vis_spr(all, all->visible_sprite, num_visible_sprite);
}
