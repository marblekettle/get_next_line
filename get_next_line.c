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
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

char	is_last_line(int fd, char *buffer, int *ind, int *c)
{
	(*ind)++;
	(*c)--;
	if (*ind == BUFFER_SIZE)
		*ind = 0;
	if (*c < 1)
		*c = read(fd, buffer, BUFFER_SIZE);
	if (*c < 1)
		return (0);
	else
		return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	buf[BUFFER_SIZE];
	static int	index = -1;
	static int	cread = 0;
	int			sindex;

	if (!refresh(line, (index == -1), &index))
		return (-1);
	while (1)
	{
		sindex = index;
		if (cread < 1)
			cread = read(fd, buf, BUFFER_SIZE);
		if (cread < 1)
			return (cread);
		index = find_next_line(buf, index, &cread);
		if (!append(line, buf, sindex, index))
			return (-1);
		if (index != BUFFER_SIZE)
			break ;
		index = 0;
	}
	return (is_last_line(fd, buf, &index, &cread));
}
