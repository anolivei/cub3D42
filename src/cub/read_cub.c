/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/24 18:16:45 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	count_coluns(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
		i++;
	return (i);
}

int	read_cub(t_all *all, char *file, int argc)
{
	int		ret;
	int		fd;
	int		posic;
	
	posic = 0;
	ret = 1;
	if (argc == 2)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Error reading file\n", 1);
			return (0);
		}
	}
	else
	{
		ft_putstr_fd("Choose a map", 1);
		return (0);
	}
	ret = get_next_line(fd, &all->data.line);
	while (ret > 0)
	{
		verify_data(all, posic);
		free(all->data.line);
		all->data.line = NULL;
		ret = get_next_line(fd, &all->data.line);
		posic++;
	}
	free(all->data.line);
	all->data.line = NULL;
	return(1);
}

void	verify_data(t_all *all, int posic)
{
	char		**ret;
	
	if (all->data.line[0] == 0)
		all->data.error = 1;
	ret = ft_split(all->data.line, ' ');
	if (ret[0] != NULL)
	{
		if (ft_strncmp(ret[0], "R", 1) == 0 && posic == 0)
		{
			all->data.scr_weig = ft_atoi(ret[1]);
			all->data.scr_heig = ft_atoi(ret[2]);
		}
		if (ft_strncmp(ret[0], "NO", 2) == 0)
			all->data.NO = ret[1];
		if (ft_strncmp(ret[0], "SO", 2) == 0)
			all->data.SO = ret[1];
		if (ft_strncmp(ret[0], "WE", 2) == 0)
			all->data.WE = ret[1];
		if (ft_strncmp(ret[0], "EA", 2) == 0)
			all->data.EA = ret[1];
		if (ft_strncmp(ret[0], "F", 1) == 0 && ret[0][1] == '\0')
			all->data.floor = convert_colors(ret[1]);
		if (ft_strncmp(ret[0], "C", 1) == 0 && ret[0][1] == '\0')
			all->data.ceil = convert_colors(ret[1]);
		if (ft_strncmp(ret[0], "S", 1) == 0 && ret[0][1] == '\0')
			all->data.sprite = ret[1];
		free(ret);
		ret = NULL;
		if (all->data.line[0] == '0' || all->data.line[0] == '1' || all->data.line[0] == '2')
		{
			if (all->data.len_x_map < count_coluns(all->data.line))
				all->data.len_x_map = count_coluns(all->data.line);
			all->data.map_line = ft_strjoin(all->data.map_line, all->data.line);
			all->data.map_line = ft_strjoin(all->data.map_line, "\n");
			all->data.len_y_map ++;
		}
	}
}

void	allocate_map(t_all *all, int i, int j, int p)
{
	all->data.map = malloc((all->data.len_y_map +1) * sizeof(char*) + 1);
	all->data.map[0] = malloc((all->data.len_x_map +1) * sizeof(char*) + 1);
	while (all->data.map_line[p] != '\0')
	{
		if (all->data.map_line[p] == '\n')
		{
			i++;
			j = 0;
			all->data.map[i] = malloc(all->data.len_x_map * sizeof(char*) + 1);
		}
		else
		{
			all->data.map[i][j] = all->data.map_line[p];
			if (all->data.map_line[p] == 'N' || all->data.map_line[p] == 'S' || all->data.map_line[p] == 'W' || all->data.map_line[p] == 'E')
			{
				all->player.x = j * TILE_SIZE;
				all->player.y = i * TILE_SIZE;
				all->data.orientation = all->data.map_line[p];
			}
			j++;
		}
		p++;
	}
}