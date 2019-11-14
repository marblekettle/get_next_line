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

char	refresh(char **line, char first)
{
	if (!line)
		return (0);
	if(!first)
		free(*line);
	*line = malloc(sizeof(char) * 1);
	if (!*line)
		return (0);
	**line = '\0';
	return (1);
}

char	append(char **line, char *buf, size_t len)
{
	size_t	l;
	char	*tline;

	l = 0;
	while ((*line)[l])
		l++;
	tline = malloc(sizeof(char) * (l + len + 1));
	if (!tline)
		return (0);
	copy_str(&tline, *line, 0, l);
	copy_str(&tline, buf, l, len);
	free(*line);
	*line = tline;
	return (1);
}