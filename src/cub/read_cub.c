/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/18 12:33:24 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	read_cub(t_all *all, char *file, int argc)
{
	int		ret;
	int		fd;
	int		posic;
	t_data	data;

	posic = 0;
	ret = 1;
	if (argc == 2)
	{
		if ((fd = open(file, O_RDONLY)) == -1)
		{
			ft_putstr_fd("Error reading file\n", 1);
			return (FALSE);
		}
	}
	else
	{
		ft_putstr_fd("Escolha um mapa", 1);
		return (1);
	}
	while ((ret = get_next_line(fd, &data.line)) > 0)
	{
		data = verify_data(data.line, posic, data);
		free(data.line);
		data.line = NULL;
		posic++;
	}
	return(1);
}

t_data verify_data(char *line, int posic, t_data data)
{
	int			len_split;
	char		**ret;
	
	if (line[0] == 0)
	{
		data.error = 1;
		return (data);
	}
	ret = ft_split(line, ' ');
	len_split = count_words(line, ' ');
	if (ft_strncmp(ret[0], "R", 1) == 0 && posic == 0)
	{
		data.scr_weig = ft_atoi(ret[1]);
		data.scr_heig = ft_atoi(ret[2]);
	}
	if (ft_strncmp(ret[0], "NO", 2) == 0)
		data.NO = ret[1];
	if (ft_strncmp(ret[0], "SO", 2) == 0)
		data.SO = ret[1];
	if (ft_strncmp(ret[0], "WE", 2) == 0)
		data.WE = ret[1];
	if (ft_strncmp(ret[0], "EA", 2) == 0)
		data.EA = ret[1];
	if (ft_strncmp(ret[0], "F", 1) == 0)
		data.floor = ret[1];
	if (ft_strncmp(ret[0], "C", 1) == 0)
		data.ceil = ret[1];
	free(ret);
	ret = NULL;
	if (line[0] == '0' || line[0] == '1' || line[0] == 2)
	{
		data.map_line = ft_strjoin(data.map_line, line);
		data.map_line = ft_strjoin(data.map_line, "\n");
		if (data.len_x_map < len_split)
			data.len_x_map = len_split;
		data.len_y_map ++;
	}
	return (data);
}
