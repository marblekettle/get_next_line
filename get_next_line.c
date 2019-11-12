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
	unsigned int	i;
	char			c;
	char			buf[BUFFER_SIZE];

	i = 0;
	c = 1;
	while (c != '\n' && c != '\0')
	{
		read(fd, &c, 1);
		if (c == '\n' || c == '\0')
			break ;
		buf[i] = c;
		i++;
		if (i == BUFFER_SIZE)
		{
			allocat(line, buf);
			i = 0;
		}
	}
	buf[i] = '\0';
	allocat(line, buf);
	return (c ? 1 : 0);
}

int		main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDWR);
	while(get_next_line(fd, &line)
		printf("%s\n", line);
	return (0);
}
