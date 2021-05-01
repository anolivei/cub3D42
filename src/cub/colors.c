/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:14:55 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/01 15:07:14 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_color_number(int r, int g, int b)
{
	if (r > 255 || r < 0 || g > 255 || g < 0
		|| b > 255 || b < 0)
	{
		ft_putstr_fd("Invalid color", 1);
	}
}

int	convert_colors(char *color)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	colors = ft_split(color, ',');
	if (colors[0] != 0)
		r = ft_atoi(colors[0]);
	if (colors[1] != 0)
		g = ft_atoi(colors[1]);
	if (colors[2] != 0)
		b = ft_atoi(colors[2]);
	check_color_number(r, g, b);
	free_array((void *) colors);
	return (r << 16 | g << 8 | b);
}

void	free_array(void **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}
