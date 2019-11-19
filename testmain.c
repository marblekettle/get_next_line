#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		c;
	char	eh;

	if (ac == 2)
		fd = open(av[1], O_RDWR);
	else
		fd = 0;
	while (1)
	{
		c = get_next_line(fd, &line);
		printf("%s - %i\n", line, c);
		read(0, &eh, 1);
		if (c == 0 || c == -1)
			break ;
	}
	return (0);
}
