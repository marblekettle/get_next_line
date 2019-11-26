/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:10:51 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/06 13:16:26 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	buf_flush(t_fd *fdl)
{
	unsigned int i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		(fdl->buf)[i] = '\0';
		i++;
	}
}

int		buf_fill(t_fd *fdl)
{
	if (fdl->cread <= 0)
	{
		buf_flush(fdl);
		fdl->cread = read(fdl->fdnum, fdl->buf, BUFFER_SIZE);
		fdl->index = 0;
	}
	return (fdl->cread);
}

void	copy_str(char **dst, char *src, size_t start, size_t len)
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
	while ((fdl->buf)[i] && (fdl->buf)[i] != '\n' && i < BUFFER_SIZE)
		i++;
	return (i);
}

char	append(char **line, t_fd *fdl)
{
	size_t	l;
	size_t	nindex;
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
