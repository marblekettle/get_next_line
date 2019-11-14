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
	int					err;

	if(!refresh(line, (index == BUFFER_SIZE)))
		return (-1);
	while (1)
	{
		if (index == BUFFER_SIZE || buf[index] == '\0')
		{
			index = 0;
			err = read(fd, buf, BUFFER_SIZE);
			if (err == 0 || err == -1)
				return (err);
		}
		if (buf[index] == '\n')
		{
			if (!append(line, buf, index))
				return (-1);
			index++;
			return (1);
		}
		index++;
		if (index == BUFFER_SIZE)
			append(line, buf, index);
	}
}

int		main(void)
{
 	int		fd;
	char	*line;
	int		c;

	fd = open("./test1.txt", O_RDWR);
	//fd = 0;
	while(1)
	{
		c = get_next_line(fd, &line);
		printf("%s - %i\n", line, c);
		if (c == 0 || c == -1)
			break ;
	} 
/*	char	*b;

	refresh(&b, 1);
	append(&b, "fghij", 5);
	append(&b, "fghij", 3);
	printf("%s\n", b);
	refresh(&b, 0);
	append(&b, "fghij", 5);
	printf("%s\n", b);
	refresh(&b, 0); */
	return (0);
}
