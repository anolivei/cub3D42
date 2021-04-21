/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/21 18:55:54 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
		printf("%s %d\n", all->data.line, posic);
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
	int			len_split;
	char		**ret;
	
	if (all->data.line[0] == 0)
		all->data.error = 1;
	ret = ft_split(all->data.line, ' ');
	len_split = count_words(all->data.line, ' ');
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
		if (ft_strncmp(ret[0], "F", 1) == 0)
			all->data.floor = ret[1];
		if (ft_strncmp(ret[0], "S", 1) == 0 && ret[0][1] == '\0')
			all->data.sprite = ret[1];
		if (ft_strncmp(ret[0], "C", 1) == 0)
			all->data.ceil = ret[1];
		free(ret);
		ret = NULL;
		if (all->data.line[0] == '0' || all->data.line[0] == '1' || all->data.line[0] == 2)
		{
			all->data.map_line = ft_strjoin(all->data.map_line, all->data.line);
			all->data.map_line = ft_strjoin(all->data.map_line, "\n");
			if (all->data.len_x_map < len_split)
				all->data.len_x_map = len_split;
			all->data.len_y_map ++;
		}
	}
}
