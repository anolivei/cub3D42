/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anolivei <anolivei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 17:53:16 by anolivei          #+#    #+#             */
/*   Updated: 2021/05/02 14:43:13 by anolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	gnl_end_line(char *s_line)
{
	int	i;

	i = 0;
	if (s_line == 0)
		return (-1);
	while (s_line[i] != '\0')
	{
		if (s_line[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	gnl_return_line(char **s_line, char **line)
{
	int		i;
	char	*tmp;

	i = gnl_end_line(*s_line);
	if (i >= 0)
	{
		*line = ft_substr(*s_line, 0, i);
		tmp = ft_substr(*s_line, i + 1, ft_strlen_gnl(*s_line));
		free(*s_line);
		*s_line = tmp;
		tmp = NULL;
		return (1);
	}
	else
		return (0);
}

static void	gnl_allocate(t_gnl *gnl, int fd)
{
	if (gnl->s_l[fd] == NULL)
		gnl->s_l[fd] = ft_strdup(gnl->buff);
	else
		gnl->s_l[fd] = ft_strjoin_gnl(gnl->s_l[fd], gnl->buff, 0, 0);
}

int	get_next_line(int fd, char **line, t_gnl *gnl)
{
	if (line == 0 || fd < 0 || BUFFER_SIZE == 0)
		return (-1);
	if (gnl->s_l[fd] != NULL)
	{
		if (gnl_return_line(&gnl->s_l[fd], line) == 1)
			return (1);
	}
	gnl->s_l[fd] = ft_strdup("");
	gnl->ret = read(fd, gnl->buff, BUFFER_SIZE);
	while (gnl->ret > 0)
	{
		gnl->buff[gnl->ret] = '\0';
		gnl_allocate(gnl, fd);
		if (gnl->s_l[fd] == 0)
			return (-1);
		if (gnl_return_line(&gnl->s_l[fd], line) == 1)
			return (1);
	}
	if (gnl->ret < 0)
		*line = NULL;
	else
		*line = gnl->s_l[fd];
	gnl->s_l[fd] = NULL;
	return (gnl->ret);
}
