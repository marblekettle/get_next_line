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
#include <stdio.h>
#include <fcntl.h>

int		get_next_line(int fd, char **line)
{
	static char			buf[BUFFER_SIZE];
	static unsigned int	index = BUFFER_SIZE;

	if(!refresh(line, (index == BUFFER_SIZE)))
		return (-1);
	while (1)
	{
		if (index == BUFFER_SIZE)
		{
			if(!read(fd, buf, BUFFER_SIZE))
				return (-1);
			index = 0;
		}
		if (buf[index] == '\n' || buf[index] == '\0')
		{
			if (!append(line, buf, index))
				return (-1);
			if (buf[index] == '\n')
				index++;
			return ((buf[index]) ? 1 : 0);
		}
		index++;
		if (index == BUFFER_SIZE)
			append(line, buf, index);
		printf("%s - %s\n", buf, *line);
	}
}

int		main(void)
{
	int		fd;
	char	*line;

	//fd = open("./test.txt", O_RDWR);
	fd = 0;
	while(get_next_line(fd, &line) == 1)
		printf("%s\n", line);
	return (0);
}
