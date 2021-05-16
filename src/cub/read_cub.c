/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 22:27:13 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	count_coluns(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
		i++;
	return (i);
}

static int	verify_args(t_all *all, int argc, char *file)
{
	int	fd;

	if (argc == 2 || argc == 3)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			all->error.msg = ft_strjoin(all->error.msg, "\nCan't read file\n");
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

static int	verify_read(t_all *all)
{
	if (all->error.floor > 0 && all->error.ceil > 0
		&& all->error.no > 0 && all->error.so > 0
		&& all->error.ea > 0 && all->error.we > 0
		&& all->error.sprite > 0)
		return (1);
	return (0);
}

void	verify_data(t_all *all, int posic)
{
	char	**ret;

	if (((all->data.line[0] == '0' || all->data.line[0] == '1'
				|| all->data.line[0] == ' ') && verify_read(all))
		|| (all->data.line[0] == '\0' && all->data.len_x_map > 0))
	{
		if (all->data.len_x_map < count_coluns(all->data.line))
			all->data.len_x_map = count_coluns(all->data.line);
		all->data.map_line = ft_strjoin(all->data.map_line, all->data.line);
		all->data.map_line = ft_strjoin(all->data.map_line, "\n");
		all->data.len_y_map++;
	}
	ret = ft_split(all->data.line, ' ');
	if (ret[0] != NULL && all->data.len_y_map == 0)
		put_data_on_struct(all, ret, &all->data, posic);
	free_array((void *)ret);
}

int	read_cub(t_all *all, char *file, int argc, int posic)
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
		verify_data(all, posic);
		free(all->data.line);
		all->data.line = NULL;
		ret = get_next_line(fd, &all->data.line, &all->gnl);
		posic++;
	}
	free_check(all->data.line);
	close(fd);
	return (1);
}
