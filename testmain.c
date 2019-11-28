#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	*line;
	int		c;

	fd2 = 0;
	if (ac == 3)
	{
		fd = open(av[1], O_RDWR);
		fd2 = open(av[2], O_RDWR);
	}
	else if (ac == 2)
		fd = open(av[1], O_RDWR);
	else
		fd = 0;
	c = 1;
	while (c > 0)
	{
		c = get_next_line(fd, &line);
		printf("%s - %i\n", line, c);
		free(line);
		if (fd2 != 0)
		{
			c = get_next_line(fd2, &line);
			printf("%s - %i\n", line, c);
			free(line);
		}
	}
	return (0);
}
