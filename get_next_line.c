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
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static char	init_fd(t_fd **fdl, t_fd **target, int fd)
{
	if (!*fdl)
	{
		*fdl = (t_fd *)malloc(sizeof(t_fd));
		if (!*fdl)
			return (0);
		(*fdl)->fdnum = fd;
		(*fdl)->index = 0;
		(*fdl)->cread = 0;
		(*fdl)->next = NULL;
		*target = *fdl;
		return (1);
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

int			get_next_line(int fd, char **line)
{
	static t_fd	*fdlist = NULL;
	t_fd		*target;
	char		*tline;

	if (!init_fd(&fdlist, &target, fd) || !init_line(&tline))
		return (-1);
	if ((target->buf)[target->index] == '\n')
	{
		(target->index)++;
		(target->cread)--;
	}
	while (buf_fill(target) > 0)
	{
		if (!append(&tline, target))
			return (-1);
		if ((target->buf)[target->index] == '\n')
			break ;
	}
	if (target->cread >= 0)
		*line = tline;
	return (target->cread > 0 ? 1 : target->cread);
}
