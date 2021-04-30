/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 20:57:18 by anolivei          #+#    #+#             */
/*   Updated: 2021/04/28 22:23:01 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	size_t	a_len;
	char	*aux;

	aux = b;
	a_len = len;
	i = 0;
	while (a_len > 0)
	{
		if (aux[i] != '\0' || i < len)
			aux[i] = c;
		i++;
		a_len--;
	}
	return (aux);
}
