/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/13 19:14:39 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	read_cub(t_all *all, char *file)
{
	int	ret;
	int	fd;

	ret = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Error reading file\n", 1);
		return (FALSE);
	}
	while (ret != 0)
	{
		ret = get_next_line(fd, &all->map.line);
	}


	

}