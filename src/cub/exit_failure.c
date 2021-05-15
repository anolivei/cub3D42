/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:57:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 20:36:02 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	freeing_error(t_all *all)
{
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
	if (all->gnl.tmp > 0 && all->error.double_map == 99)
		free_check(all->gnl.tmp);
	free_check(all->gnl.s_l[0]);
	all->gnl.buff[0] = '\0';
	free(all->error.msg);
}

static void	freeing_all(t_all *all)
{
	free_check(all->img.img_ptr);
	free_check(all->text.east.img_ptr);
	free_check(all->text.south.img_ptr);
	free_check(all->text.north.img_ptr);
	free_check(all->text.west.img_ptr);
	free_check(all->text.sprite.img_ptr);
	free_check(all->bmp.buff_body);
	free_check(all->error.msg);
}

int	destroy_window(t_all *all)
{
	freeing_all(all);
	exit(0);
	return (1);
}

void	exit_failure(t_all *all)
{
	if (ft_strlen(all->error.msg) > 0)
	{
		ft_putstr_fd("Error", 1);
		ft_putstr_fd(all->error.msg, 1);
		ft_putstr_fd("\n", 1);
		freeing_error(all);
		exit (0);
	}
}
