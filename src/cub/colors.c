/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:14:55 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/09 01:14:06 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	check_color_number(int r, int g, int b)
{
	if (r > 255 || r < 0 || g > 255 || g < 0
		|| b > 255 || b < 0)
	{
		ft_putstr_fd("Invalid color\n", 1);
		exit(0);
	}
}

static int	verify_number(char *number)
{
	size_t t;

	t = 0;
	while (t < ft_strlen(&number[t]) || number[t] != '\0')
	{
		if (!ft_isdigit(number[t]))
			return (0);
		t++;
	}
	return (1);
}

int	convert_colors(char *color)
{
	char	**colors;
	int		r;
	int		g;
	int		b;

	r = -1;
	g = -1;
	b = -1;
	colors = ft_split(color, ',');
	if (colors[0] != 0 && verify_number(colors[0]))
		r = ft_atoi(colors[0]);
	if (colors[1] != 0 && verify_number(colors[1]))
		g = ft_atoi(colors[1]);
	if (colors[2] != 0 && verify_number(colors[2]))
		b = ft_atoi(colors[2]);
	if (colors[3])
	{
		ft_putstr_fd("So much arguments in colors\n", 1);
		exit(0);
	}
	check_color_number(r, g, b);
	free_array((void *) colors);
	return (r << 16 | g << 8 | b);
}
