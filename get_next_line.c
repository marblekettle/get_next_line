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

static void	buf_flush(char *buf)
{
	unsigned int i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buf[i] = '\0';
		i++;
	}
}

static char	init_fd(t_fd **fdl, t_fd **target, int fd)
{
	if (!*fdl)
	{
		*fdl = (t_fd *)malloc(sizeof(t_fd));
		if (!*fdl)
			return (0);
		(*fdl)->fdnum = fd;
		(*fdl)->index = BUFFER_SIZE;
		(*fdl)->cread = 0;
		(*fdl)->next = NULL;
		buf_fill((*fdl)->buf);
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

int			get_next_line(int fd, char **line)
{
	static t_fd	*fdlist = NULL;
	t_fd		*target;

	if (!init_fd(&fdlist, &target, fd))
		return (-1);

}
