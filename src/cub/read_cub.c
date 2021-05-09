/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/09 01:27:28 by anolivei         ###   ########.fr       */
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

static void	put_data_on_struct(char **ret, t_data *data, int posic)
{
	if (ft_strncmp(ret[0], "R", 1) == 0 && posic == 0)
	{
		data->scr_weig = ft_atoi(ret[1]);
		data->scr_heig = ft_atoi(ret[2]);
	}
	if (ft_strncmp(ret[0], "NO", 2) == 0)
		data->NO = ft_strdup(ret[1]);
	if (ft_strncmp(ret[0], "SO", 2) == 0)
		data->SO = ft_strdup(ret[1]);
	if (ft_strncmp(ret[0], "WE", 2) == 0)
		data->WE = ft_strdup(ret[1]);
	if (ft_strncmp(ret[0], "EA", 2) == 0)
		data->EA = ft_strdup(ret[1]);
	if (ft_strncmp(ret[0], "F", 1) == 0 && ret[0][1] == '\0')
		data->floor = convert_colors(ret[1]);
	if (ft_strncmp(ret[0], "C", 1) == 0 && ret[0][1] == '\0')
		data->ceil = convert_colors(ret[1]);
	if (ft_strncmp(ret[0], "S", 1) == 0 && ret[0][1] == '\0')
		data->sprite = ft_strdup(ret[1]);
}

static int	verify_args(int argc, char *file)
{
	int	fd;

	if (argc == 2 || argc == 3)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Error reading file\n", 1);
			return (0);
		}
		else
			return (fd);
	}
	else
	{
		ft_putstr_fd("Choose a map", 1);
		return (0);
	}
}

void	verify_data(t_all *all, int posic)
{
	char	**ret;

	if (all->data.line[0] == 0)
		all->data.error = 1;
	ret = ft_split(all->data.line, ' ');
	if (ret[0] != NULL)
	{
		put_data_on_struct(ret, &all->data, posic);
		if (all->data.line[0] == '0' || all->data.line[0] == '1'
			|| all->data.line[0] == '2')
		{
			if (all->data.len_x_map < count_coluns(all->data.line))
				all->data.len_x_map = count_coluns(all->data.line);
			all->data.map_line = ft_strjoin(all->data.map_line, all->data.line);
			all->data.map_line = ft_strjoin(all->data.map_line, "\n");
			all->data.len_y_map++;
		}
	}
	free_array((void *)ret);
}

int	read_cub(t_all *all, char *file, int argc, int posic)
{
	int	ret;
	int	fd;

	fd = verify_args(argc, file);
	if (fd == 0)
		return (0);
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
