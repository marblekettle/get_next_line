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

/* init_fd: Searches in chained file descriptor list 'fdl' for a link whose
** file descriptor number matches 'fd' and returns it in pointer 'target'. If
** no link is found that matches, it allocates a new link for that file
** descriptor and appends it to the chained list before returning it.
** Return value: 1 if memory allocation is successful, 0 upon allocation error
** or if the file descriptor number or buffer size are invalid.
*/

static char	init_fd(t_fd **fdl, t_fd **target, int fd)
{
	if (fd < 0 || (int)BUFFER_SIZE <= 0)
		return (0);
	if (!*fdl)
	{
		*fdl = (t_fd *)malloc(sizeof(t_fd));
		if (!*fdl)
			return (0);
		(*fdl)->fdnum = fd;
		(*fdl)->index = 0;
		(*fdl)->cread = 0;
		(*fdl)->next = NULL;
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

/* init_line: allocates a new empty string and returns it to pointer 'line'.
** Return value: 1 if memory allocation is successful, 0 upon allocation error
** or if argument 'line' points to nothing.
*/

static char	init_line(char **line)
{
	if (!line)
		return (0);
	*line = malloc(sizeof(char) * 1);
	if (!*line)
		return (0);
	**line = '\0';
	return (1);
}

/* seek_and_destroy: searches in linked file descriptor list 'fdl' for a link
** with a file descriptor number that matches 'fd'. If it finds it, it pops it
** out of the list, tying the pointer to it to its next link, and frees it.
*/

static void	seek_and_destroy(t_fd **fdl, int fd)
{
	t_fd	*temp;

	if ((*fdl)->fdnum == fd)
	{
		temp = *fdl;
		*fdl = (*fdl)->next;
		free(temp);
	}
	else
		seek_and_destroy(&((*fdl)->next), fd);
}

/* close_gnl: determines if the end of a file has been reached by checking
** the current file descriptor 'target's 'cread' member. If it is greater than
** one, which means a newline has broken the main function's loop, it will skip
** this newline so the next function call starts at the first character after.
** If cread is 0 or -1, indicating an end-of-file or error, it removes the link
** for this file descriptor 'target' from the file descriptor list 'fdl'.
** Return value: 1 if cread is greater than 0 and there are still characters to
** be read. 0 if the end-of-file has been reached, and -1 if an error occurred
** last time function 'read' was run.
*/

static int	close_gnl(t_fd **fdl, t_fd *target)
{
	int		c;

	c = target->cread;
	if (c > 0)
	{
		(target->index)++;
		(target->cread)--;
		return (1);
	}
	seek_and_destroy(fdl, target->fdnum);
	return (c);
}

/* get_next_line: reads from file descriptor 'fd' and returns a line of
** characters - that is - all characters up to the next newline (\n), returning
** a pointer to it to 'line' only if the function returns a 1 or a 0. The space
** for this line is dynamically allocated in this case, and memory management
** is to be handled by the user. The function creates separate buffers for
** different file descriptors, with size defined by compile-time constant
** 'BUFFER_SIZE'.
** Return value: 1 if a newline is reached. 0 if end-of-file is reached. -1 if
** reading the file returns an error, or memory allocation fails anywhere.
*/

int			get_next_line(int fd, char **line)
{
	static t_fd	*fdlist = NULL;
	t_fd		*target;
	char		*tline;

	if (!init_fd(&fdlist, &target, fd) || !init_line(&tline))
		return (-1);
	while (buf_fill(target) > 0)
	{
		if (!append(&tline, target))
		{
			free(tline);
			return (-1);
		}
		if ((target->buf)[target->index] == '\n')
			break ;
	}
	if (target->cread >= 0)
		*line = tline;
	return (close_gnl(&fdlist, target));
}
