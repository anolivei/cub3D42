/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:31:34 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/01 14:34:30 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	setup_player(t_all *all, t_player *player)
{
	all->player.x *= all->data.tile_size;
	all->player.y *= all->data.tile_size;
	player->width = 1;
	player->height = 1;
	player->turn_dir = 0;
	player->walk_dir = 0;
	player->walk_dir_side = 0;
	if (all->data.orientation == 'W')
		player->rot_angle = PI;
	else if (all->data.orientation == 'E')
		player->rot_angle = 0;
	else if (all->data.orientation == 'N')
		player->rot_angle = 1.5 * PI;
	else if (all->data.orientation == 'S')
		player->rot_angle = 0.5 * PI;
	player->walk_speed = 20;
	player->turn_speed = 10 * (PI / 180);
	all->bmp.buff_body = malloc(sizeof(int) * (all->data.scr_weig + 1)
			* (all->data.scr_heig + 1));
	if (!all->bmp.buff_body)
		ft_putstr_fd("Fail allocating 'cub->bmp.buff_body'", 1);
}

void	setup_map(t_all *all)
{
	all->data.map_line = ft_strdup("");
	all->data.len_x_map = 0;
	all->data.len_y_map = 0;
	all->data.num_sprites = 0;
}

void	setup_texture(t_all *all, t_text *text)
{
	text->north.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
			all->data.NO, &text->north.width, &text->north.height);
	text->north.addr = mlx_get_data_addr(text->north.img_ptr,
			&text->north.bpp, &text->north.size_l, &text->north.endian);
	text->south.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
			all->data.SO, &text->south.width, &text->south.height);
	text->south.addr = mlx_get_data_addr(text->south.img_ptr,
			&text->south.bpp, &text->south.size_l, &text->south.endian);
	text->east.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
			all->data.EA, &text->east.width, &text->east.height);
	text->east.addr = mlx_get_data_addr(text->east.img_ptr,
			&text->east.bpp, &text->east.size_l, &text->east.endian);
	text->west.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
			all->data.WE, &text->west.width, &text->west.height);
	text->west.addr = mlx_get_data_addr(text->west.img_ptr,
			&text->west.bpp, &text->west.size_l, &text->west.endian);
	text->sprite.img_ptr = mlx_xpm_file_to_image(all->mlx.init,
			all->data.sprite, &text->sprite.width, &text->sprite.height);
	text->sprite.addr = mlx_get_data_addr(text->sprite.img_ptr,
			&text->sprite.bpp, &text->sprite.size_l, &text->sprite.endian);
}

void	put_textures_in_a_array(t_text *text)
{
	text->res_text[0] = text->north.width;
	text->res_text[1] = text->north.height;
	text->res_text[2] = text->south.width;
	text->res_text[3] = text->south.height;
	text->res_text[4] = text->east.width;
	text->res_text[5] = text->east.height;
	text->res_text[6] = text->west.width;
	text->res_text[7] = text->west.height;
}

void	choose_tile_size(t_data *data, t_text *text)
{
	int	i;
	int	j;
	int	tmp;

	put_textures_in_a_array(text);
	i = 0;
	while (i < 7)
	{
		j = 0;
		while (j < 7 - i)
		{
			if (text->res_text[j] > text->res_text[j + 1])
			{
				tmp = text->res_text[j];
				text->res_text[j] = text->res_text[j + 1];
				text->res_text[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	data->tile_size = text->res_text[0];
}
