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
	static char	buf[BUFFER_SIZE];
	static int	index = 0;
	static int	cread = 0;
	int			sindex;

	if(!refresh(line, (index == 0)))
		return (-1);
	sindex = index;
	while (1)
	{
		if (cread == 0)
		{
			cread = read(fd, buf, BUFFER_SIZE);
			if (cread < 1)
				return (cread);
		}
		if (buf[index] == '\n')
		{
			append(line, buf, sindex, index);
			index = (index + 1) % BUFFER_SIZE;
			cread--;
			return (1);
		}
		if (index == BUFFER_SIZE)
		{
			append (line, buf, sindex, BUFFER_SIZE);
			sindex = 0;
		}
		index = (index + 1) % BUFFER_SIZE;
		cread--;
	}
}

/* case1: cread != 0 && index != BUFFER_SIZE
** case2: cread != 0 && index == BUFFER_SIZE
** case3: cread == 0 && index != BUFFER_SIZE
*/

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
