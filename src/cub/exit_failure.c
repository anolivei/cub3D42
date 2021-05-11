/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_failure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:57:50 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/11 00:59:31 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	exit_failure(t_all *all)
{
	if (all->error.msg)
	{
		ft_putstr_fd(all->error.msg, 1);
		exit (0);
	}
}
