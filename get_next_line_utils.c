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

int		find_next_line(char *buf, int i, int *c)
{
	while (buf[i] && buf[i] != '\n' && i < BUFFER_SIZE && *c > 0)
	{
		i++;
		(*c)--;
	}
	return (i);
}

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

char	refresh(char **line, char first, int *ind)
{
	if (!line)
		return (0);
	if (first)
		*ind = 0;
	else
		free(*line);
	*line = malloc(sizeof(char) * 1);
	if (!*line)
		return (0);
	**line = '\0';
	return (1);
}

char	append(char **line, char *buf, size_t start, size_t end)
{
	size_t	l;
	char	*tline;

	l = 0;
	while ((*line)[l])
		l++;
	tline = malloc(sizeof(char) * (l + end - start + 1));
	if (!tline)
		return (0);
	copy_str(&tline, *line, 0, l);
	copy_str(&tline, buf + start, l, end - start);
	free(*line);
	*line = tline;
	return (1);
}
