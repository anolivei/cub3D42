/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 21:16:44 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/01 14:59:10 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	put_in_buffer(unsigned char *buff, unsigned int x)
{
	buff[0] = (unsigned char)(x);
	buff[1] = (unsigned char)(x >> 8);
	buff[2] = (unsigned char)(x >> 16);
	buff[3] = (unsigned char)(x >> 24);
}

static void	body_bmp(t_all *all, t_bmp *bmp, int fd)
{
	int	weig;
	int	heig;
	int	i;

	i = 0;
	heig = all->data.scr_heig - 1;
	while (heig >= 0)
	{
		weig = 0;
		while (weig < all->data.scr_weig)
			bmp->buff_body[i++] = pick_pixel(&all->img, weig++, heig);
		heig--;
	}
	if (!(write(fd, &bmp->buff_body[0], all->data.scr_heig
				* all->data.scr_weig * 4)))
		ft_putstr_fd("Couldn't write the body of the bmp file\n", 1);
}

static void	header_bmp(t_all *all, t_bmp *bmp, int fd)
{
	unsigned int	len;

	ft_memset(&bmp->buff_header, 0, 54);
	len = (all->data.scr_heig) * (all->data.scr_weig) * (all->img.bpp / 8) + 54;
	bmp->buff_header[0] = 0x42;
	bmp->buff_header[1] = 0x4D;
	put_in_buffer(&bmp->buff_header[2], len);
	bmp->buff_header[10] = (0x36);
	bmp->buff_header[14] = (0x28);
	put_in_buffer(&bmp->buff_header[18], all->data.scr_weig);
	put_in_buffer(&bmp->buff_header[22], all->data.scr_heig);
	bmp->buff_header[26] = (0x1);
	put_in_buffer(&bmp->buff_header[28], all->img.bpp);
	if (!(write(fd, &bmp->buff_header, 54)))
		ft_putstr_fd("Couldn't write the header of the bmp file\n", 1);
}

void	save_image_bmp(t_all *all)
{
	int	fd;

	fd = open("img.bmp", O_CREAT | O_WRONLY | O_TRUNC, 444);
	if (fd == -1)
		ft_putstr_fd("Error creating bmp file\n", 1);
	render(all);
	header_bmp(all, &all->bmp, fd);
	body_bmp(all, &all->bmp, fd);
	close(fd);
	destroy_window(all);
}
