/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:10:51 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/06 13:16:26 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

/* buf_flush: a version of ft_bzero tailored to work with the buffer of
** linked file descriptor lists. Makes sure the buffer is clean after being
** completely read.
*/

void	buf_flush(t_fd *fdl)
{
	unsigned int i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		(fdl->buf)[i] = '\0';
		i++;
	}
}

/* buf_fill: calls 'read' if the buffer has been completely read and returns
** its return value. Otherwise, returns the number of characters left to read
** from the buffer.
*/

int		buf_fill(t_fd *fdl)
{
	if (fdl->cread <= 0)
	{
		buf_flush(fdl);
		fdl->cread = read(fdl->fdnum, fdl->buf, BUFFER_SIZE);
		fdl->index = 0;
	}
	return (fdl->cread);
}

/* copy_str: a version of ft_strlcpy with an added 'start' parameter to specify
** where to start copying to in 'dst'. Also always terminates with a null char.
*/

void	copy_str(char **dst, char *src, size_t start, size_t len)
{
	size_t i;

	if (!dst || !src)
		return ;
	i = 0;
	while (i < len && src[i] != '\0')
	{
		(*dst)[i + start] = src[i];
		i++;
	}
	(*dst)[i + start] = '\0';
}

/* find_next_line: a version of ft_strchr tailored to work with the chained
** file descriptor list. It returns the index in the buffer of the next
** occurrence of a newline. If no newlines are found, it returns the value
** of BUFFER_SIZE.
*/

int		find_next_line(t_fd *fdl)
{
	size_t	i;

	i = fdl->index;
	while ((fdl->buf)[i] && (fdl->buf)[i] != '\n' && i < BUFFER_SIZE)
		i++;
	return (i);
}

/* append: a version of ft_strjoin tailored to work with the chained file
** descriptor list. It joins the buffer or part of the buffer from the current
** index member to the next occurence of a newline to the end of the string
** pointed to by 'line', by copying the contents of both to a newly allocated
** string and freeing the old line. As such, 'line' has to be a string that is
** dynamically allocated (explaining the necessity of line_init). It returns
** 1 upon success and 0 upon a memory allocation error.
*/

char	append(char **line, t_fd *fdl)
{
	size_t	l;
	size_t	nindex;
	size_t	nl;
	char	*tline;

	l = 0;
	while ((*line)[l])
		l++;
	nindex = find_next_line(fdl);
	nl = nindex - fdl->index;
	tline = malloc(sizeof(char) * (l + nl + 1));
	if (!tline)
		return (0);
	copy_str(&tline, *line, 0, l);
	copy_str(&tline, fdl->buf + fdl->index, l, nl);
	fdl->cread -= nl;
	fdl->index = nindex;
	free(*line);
	*line = tline;
	return (1);
}
