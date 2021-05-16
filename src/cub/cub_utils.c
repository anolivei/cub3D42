/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 01:52:12 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/16 03:11:39 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
	{
		angle = TWO_PI + angle;
	}
	return (angle);
}

float	distance_between_points(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	free_array(void **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_check(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

char	*remove_space(t_all *all, char *color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	all->aux = malloc((ft_strlen(color)) * sizeof(char *) + 1);
	while (color[i] != '\0')
	{
		if (color[i] != ' ' && color[i] != '\t' )
		{
			all->aux[j] = color[i];
			j++;
		}
		i++;
	}
	return (all->aux);
}
