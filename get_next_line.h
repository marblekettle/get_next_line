/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:11:18 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/06 13:15:30 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# include <stddef.h>

int		get_next_line(int fd, char **line);
int		find_next_line(char *buf, int i, int *c);
void	copy_str(char **dst, char *src, size_t start, size_t len);
char	append(char **line, char *buf, size_t start, size_t end);
char	refresh(char **line, char first, int *ind);

#endif
