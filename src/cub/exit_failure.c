/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:57:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/14 23:35:38 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	exit_failure(t_all *all)
{
	if (all->error.msg)
	{
		ft_putstr_fd(all->error.msg, 1);
		if (all->data.map_line != NULL)
			free(all->data.map_line);
		if (all->error.no > 0)
			free_check(all->data.NO);
		if (all->error.so > 0)
			free_check(all->data.SO);
		if (all->error.we > 0)
			free_check(all->data.WE);
		if (all->error.ea > 0)
			free_check(all->data.EA);
		if (all->error.sprite > 0)
			free(all->data.sprite);

		printf("*%s*\n",all->gnl.buff);
		printf("*%s*\n",all->gnl.s_l[0]);
		free_check(all->gnl.s_l[0]);
		all->gnl.buff[0] = '\0';

		//free_check(all->gnl.buff);

		//printf("*%s*\n",all->gnl.tmp);



		//free_array((void *)all->data.map_line);
		//free_check(all->data.line);
		//free_check(all->data.map_line);

		//if (all->data.sprite != NULL)
		//	free(all->data.sprite);
		/*if (all->data.map != NULL)
		{
			free(*all->data.map);
			free(all->data.map);
		}*/
		/*if (all->text.north.img_ptr != NULL)
			mlx_destroy_image(all->mlx.init, all->text.north.img_ptr);
		if (all->text.south.img_ptr != NULL)
			mlx_destroy_image(all->mlx.init, all->text.south.img_ptr);
		if (all->text.east.img_ptr != NULL)
			mlx_destroy_image(all->mlx.init, all->text.east.img_ptr);
		if (all->text.west.img_ptr != NULL)
			mlx_destroy_image(all->mlx.init, all->text.west.img_ptr);
		destroy_window(all);*/
		//free_array((void *)all->data.map);
		//free_check(all->data.line);
		//if (all->data.map[0])
		exit (0);
	}
}
