/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 17:39:27 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/15 17:39:44 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	if (n != 0)
	{
		str = (unsigned char *)s;
		s = ft_memset(s, 0, n);
	}
}
