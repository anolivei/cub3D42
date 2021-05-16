/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_data_on_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 12:52:28 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/16 02:41:55 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	verify_chars(char **ret, t_all *all)
{
	if (ft_strlen(ret[0]) == 1)
	{
		if (ft_strncmp(ret[0], "R", 1) != 0 && ft_strncmp(ret[0], "F", 1) != 0
			&& ft_strncmp(ret[0], "S", 1) != 0
			&& ft_strncmp(ret[0], "C", 1) != 0)
			all->error.msg = ft_strjoin(all->error.msg, "\nInvalid Character");
	}
	if (ft_strlen(ret[0]) == 2)
	{
		if (ft_strncmp(ret[0], "NO", 2) != 0 && ft_strncmp(ret[0], "SO", 2) != 0
			&& ft_strncmp(ret[0], "EA", 2) != 0
			&& ft_strncmp(ret[0], "WE", 2) != 0)
			all->error.msg = ft_strjoin(all->error.msg, "\nInvalid Character");
	}
}

static void	put_textures_no_so_on_struct(t_all *all, t_data *data, char **ret)
{
	if (ft_strncmp(ret[0], "NO", 2) == 0 )
	{
		if (all->error.no == 0)
			data->NO = ft_strdup(ret[1]);
		all->error.no++;
	}
	if (ft_strncmp(ret[0], "SO", 2) == 0 && ret[1] != NULL
		&& ret[2] == NULL)
	{
		if (all->error.so == 0)
			data->SO = ft_strdup(ret[1]);
		all->error.so++;
	}
}

static void	put_textures_we_ea_on_struct(t_all *all, t_data *data, char **ret)
{
	if (ft_strncmp(ret[0], "WE", 2) == 0 && ret[1] != NULL
		&& ret[2] == NULL)
	{
		if (all->error.we == 0)
			data->WE = ft_strdup(ret[1]);
		all->error.we++;
	}
	if (ft_strncmp(ret[0], "EA", 2) == 0 && ret[1] != NULL
		&& ret[2] == NULL)
	{
		if (all->error.ea == 0)
			data->EA = ft_strdup(ret[1]);
		all->error.ea++;
	}
}

void	put_floor_ceil_on_struct(t_all *all)
{
	remove_space(all, &all->data.line[2]);
	if (all->data.line[0] == 'F')
	{
		all->data.floor = convert_colors(all->aux, all);
		all->error.floor++;
	}
	if (all->data.line[0] == 'C')
	{
		all->data.ceil = convert_colors(all->aux, all);
		all->error.ceil++;
	}
	free(all->aux);
}

void	put_data_on_struct(t_all *all, char **ret, t_data *data)
{
	verify_chars(ret, all);
	if (ft_strncmp(ret[0], "R", 1) == 0 && ret[1] != NULL
		&& ret[2] != NULL && ft_strlen(ret[0]) == 1 && ret[3] == NULL)
	{
		if (verify_number(ret[1]) && verify_number(ret[2]))
		{
			data->scr_weig = ft_atoi(ret[1]);
			data->scr_heig = ft_atoi(ret[2]);
			all->error.resol++;
		}
	}
	if (ft_strlen(ret[0]) == 2 && ret[1] != NULL && ret[2] == NULL)
	{
		put_textures_no_so_on_struct(all, data, ret);
		put_textures_we_ea_on_struct(all, data, ret);
	}
	if (ft_strncmp(ret[0], "S", 1) == 0 && ret[0][1] == '\0'
		&& ret[1] != NULL && ret[2] == NULL)
	{
		if (all->error.sprite == 0)
			data->sprite = ft_strdup(ret[1]);
		all->error.sprite++;
	}
}
