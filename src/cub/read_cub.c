/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:10:22 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/10 22:45:55 by anolivei         ###   ########.fr       */
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

static void	verify_chars(char **ret)
{
	if (ft_strlen(ret[0]) == 1)
	{

		if (ft_strncmp(ret[0], "R", 1) != 0 && ft_strncmp(ret[0], "F", 1) != 0 && ft_strncmp(ret[0], "S", 1) != 0 && ft_strncmp(ret[0], "C", 1) != 0)
		{
			ft_putstr_fd("Error\nInvalid Character\n", 1);
			exit (0);
		}
	}
	if (ft_strlen(ret[0]) == 2)
	{
		if (ft_strncmp(ret[0], "NO", 2) != 0 && ft_strncmp(ret[0], "SO", 2) != 0 && ft_strncmp(ret[0], "EA", 2) != 0 && ft_strncmp(ret[0], "WE", 2)!= 0)
		{
			ft_putstr_fd("Error\nInvalid Character\n", 1);
			exit (0);
		}
	}

}

static void	put_data_on_struct(char **ret, t_data *data, int posic)
{
	verify_chars(ret);
	if (ft_strncmp(ret[0], "R", 1) == 0 && posic == 0 && ret[1] != NULL && ret[2] != NULL && ft_strlen(ret[0]) == 1 && ret[3] == NULL)
	{
		if (verify_number(ret[1]) && verify_number(ret[2]))
		{
			data->scr_weig = ft_atoi(ret[1]);
			data->scr_heig = ft_atoi(ret[2]);
			data->qtt.resol++;
		}
	}
	if (ft_strlen(ret[0]) == 2 && ret[1] != NULL && ret[2] == NULL )
	{
		if (ft_strncmp(ret[0], "NO", 2) == 0 )
		{
			data->NO = ft_strdup(ret[1]);
			data->qtt.no++;
		}
		if (ft_strncmp(ret[0], "SO", 2) == 0 && ret[1] != NULL && ret[2] == NULL)
		{
			data->SO = ft_strdup(ret[1]);
			data->qtt.so++;
		}
		if (ft_strncmp(ret[0], "WE", 2) == 0 && ret[1] != NULL && ret[2] == NULL)
		{
			data->WE = ft_strdup(ret[1]);
			data->qtt.we++;
		}
		if (ft_strncmp(ret[0], "EA", 2) == 0 && ret[1] != NULL && ret[2] == NULL)
		{
			data->EA = ft_strdup(ret[1]);
			data->qtt.ea++;
		}
	}
	if (ft_strncmp(ret[0], "F", 1) == 0 && ret[0][1] == '\0' && ret[1] != NULL && ret[2] == NULL )
	{
		data->floor = convert_colors(ret[1]);
		data->qtt.floor++;
	}
	if (ft_strncmp(ret[0], "C", 1) == 0 && ret[0][1] == '\0' && ret[1] != NULL && ret[2] == NULL )
	{
		data->ceil = convert_colors(ret[1]);
		data->qtt.ceil++;
	}
	if (ft_strncmp(ret[0], "S", 1) == 0 && ret[0][1] == '\0' && ret[1] != NULL && ret[2] == NULL)
	{
		data->sprite = ft_strdup(ret[1]);
		data->qtt.sprite++;
	}
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

static int verift_read(t_all *all)
{
	if (all->data.qtt.floor == 1 && all->data.qtt.ceil == 1 && all->data.qtt.no == 1 && all->data.qtt.so == 1
		&& all->data.qtt.ea == 1 && all->data.qtt.we == 1 && all->data.qtt.sprite == 1)
		return(1);
	return (0);
}

void	verify_data(t_all *all, int posic)
{
	char	**ret;

	if (((all->data.line[0] == '0' || all->data.line[0] == '1'
			|| all->data.line[0] == ' ') && verift_read(all)) || (all->data.line[0] == '\0' && all->data.len_x_map > 0 ) )
	{
		if (all->data.len_x_map < count_coluns(all->data.line))
			all->data.len_x_map = count_coluns(all->data.line);
		all->data.map_line = ft_strjoin(all->data.map_line, all->data.line);
		all->data.map_line = ft_strjoin(all->data.map_line, "*\n");
		all->data.len_y_map++;
	}
	ret = ft_split(all->data.line, ' ');
	if (ret[0] != NULL && all->data.len_y_map == 0)
		put_data_on_struct(ret, &all->data, posic);
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
