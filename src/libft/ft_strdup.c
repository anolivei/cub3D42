/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:01:39 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 15:01:58 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;

	len = ft_strlen(s1) + 1;
	cpy = ((char *)malloc(sizeof(char) * len));
	if (cpy != 0)
	{
		ft_strlcpy(cpy, s1, len);
		return (cpy);
	}
	else
		return (0);
}
