/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:10:05 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/06 13:16:15 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	init_fd(t_fd **fdl, t_fd **target, int fd)
{
	if (fd < 0 || (int)BUFFER_SIZE <= 0)
		return (0);
	if (!*fdl)
	{
		*fdl = (t_fd *)malloc(sizeof(t_fd));
		if (!*fdl)
			return (0);
		(*fdl)->fdnum = fd;
		(*fdl)->index = 0;
		(*fdl)->cread = 0;
		(*fdl)->next = NULL;
	}
	else if ((*fdl)->fdnum != fd)
	{
		if (!init_fd((&(*fdl)->next), target, fd))
			return (0);
		return (1);
	}
	*target = *fdl;
	return (1);
}

static char	init_line(char **line)
{
	if (!line)
		return (0);
	*line = malloc(sizeof(char) * 1);
	if (!*line)
		return (0);
	**line = '\0';
	return (1);
}

static void	seek_and_destroy(t_fd **fdl, int fd)
{
	t_fd	*temp;

	if ((*fdl)->fdnum == fd)
	{
		temp = *fdl;
		*fdl = (*fdl)->next;
		free(temp);
	}
	else
		seek_and_destroy(&((*fdl)->next), fd);
}

static int	close_gnl(t_fd **fdl, t_fd *target)
{
	int		c;

	c = target->cread;
	if (c > 0)
	{
		(target->index)++;
		(target->cread)--;
		return (1);
	}
	seek_and_destroy(fdl, target->fdnum);
	return (c);
}

int			get_next_line(int fd, char **line)
{
	static t_fd	*fdlist = NULL;
	t_fd		*target;
	char		*tline;

	if (!init_fd(&fdlist, &target, fd) || !init_line(&tline))
		return (-1);
	while (buf_fill(target) > 0)
	{
		if (!append(&tline, target))
		{
			free(tline);
			return (-1);
		}
		if ((target->buf)[target->index] == '\n')
			break ;
	}
	if (target->cread >= 0)
		*line = tline;
	return (close_gnl(&fdlist, target));
}
