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
	index++;
	cread--;
	return (1);
}
