/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 19:56:45 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/17 23:23:51 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

size_t	ft_strlen(const char *str)
{
	long int size;

	size = 0;
	while (str[size] != '\0')
	{
		size++;
	}
	return (size);
}
