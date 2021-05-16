/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/16 19:30:50 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	verify_args(t_all *all, int argc, char *file)
{
	int	fd;

	if (argc == 2 || argc == 3)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			all->error.msg = ft_strjoin(all->error.msg, "\nCan't read file");
			return (0);
		}
		else
			return (fd);
	}
	else
	{
		all->error.msg = ft_strjoin(all->error.msg, "\nWithout file .cub");
		return (0);
	}
}

int	read_cub(t_all *all, char *file, int argc)
{
	int	ret;
	int	fd;

	fd = verify_args(all, argc, file);
	if (fd == 0)
		return (0);
	all->data.line = NULL;
	all->gnl.tmp = NULL;
	all->gnl.s_l[fd] = NULL;
	ret = get_next_line(fd, &all->data.line, &all->gnl);
	while (ret > 0)
	{
		verify_data(all);
		free(all->data.line);
		all->data.line = NULL;
		ret = get_next_line(fd, &all->data.line, &all->gnl);
	}
	verify_data(all);
	free_check(all->gnl.tmp);
	close(fd);
	return (1);
}
