/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 19:28:59 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/18 18:51:33 by anolivei         ###   ########.fr       */
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

static int	verify_read(t_all *all)
{
	if (all->error.floor > 0 && all->error.ceil > 0
		&& all->error.no > 0 && all->error.so > 0
		&& all->error.ea > 0 && all->error.we > 0
		&& all->error.sprite > 0)
		return (1);
	return (0);
}

static void	verify_under_map(t_all *all)
{
	static int	map;

	if (all->data.len_x_map > 0 && map == 0)
	{
		if (all->data.line[0] == '\0' || (all->data.line[0] != '0'
				&& all->data.line[0] != '1' && all->data.line[0] != ' '))
		{
			map++;
			all->error.msg = ft_strjoin(all->error.msg,
					"\nBroken map or invalid char after map");
		}
	}
}

void	verify_data(t_all *all)
{
	char		**ret;

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
	verify_under_map(all);
	if ((all->data.line[0] == 'F' || all->data.line[0] == 'C')
		&& all->data.line[1] != '\0' )
		put_floor_ceil_on_struct(all);
	ret = ft_split(all->data.line, ' ');
	if (ret[0] != NULL && all->data.len_y_map == 0)
		put_data_on_struct(all, ret, &all->data);
	free_array((void *)ret);
}
