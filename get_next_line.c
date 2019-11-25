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

static void	buf_flush(t_fd *fdl)
{
	unsigned int i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		(fdl->buf)[i] = '\0';
		i++;
	}
}

static int	buf_fill(t_fd *fdl)
{
	if (fdl->cread <= 0)
	{
		buf_flush(fdl);
		fdl->cread = read(fdl->fdnum, fdl->buf, BUFFER_SIZE);
	}
	return (fdl->cread);
}

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

static void	copy_str(char **dst, char *src, size_t start, size_t len)
{
	size_t i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < len && src[i] != '\0')
	{
		(*dst)[i + start] = src[i];
		i++;
	}
	(*dst)[i + start] = '\0';
}

int		find_next_line(t_fd *fdl)
{
	size_t	i;

	i = fdl->index;
	while ((fdl->buf)[i] && (fdl->buf)[i] != '\n' )
		i++;
	return (i);
}

static char	append(char **line, t_fd *fdl)
{
	size_t	l;
	size_t 	nindex;
	size_t	nl;
	char	*tline;

	l = 0;
	while ((*line)[l])
		l++;
	nindex = find_next_line(fdl);
	nl = nindex - fdl->index;
	tline = malloc(sizeof(char) * (l + nl + 1));
	if (!tline)
		return (0);
	copy_str(&tline, *line, 0, l);
	copy_str(&tline, fdl->buf + fdl->index, l, nl);
	fdl->cread -= nl;
	fdl->index = nindex;
	free(*line);
	*line = tline;
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
		if(!append(&tline, target))
			return (-1);
		if ((target->buf)[target->index] == '\n')
			break ;
		if (target->index == BUFFER_SIZE)
			target->index = 0;
	}
	*line = tline;
	return (target->cread > 0 ? 1 : target->cread);
}
