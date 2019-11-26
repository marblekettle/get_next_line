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

typedef struct	s_fd
{
	int			fdnum;
	char		buf[BUFFER_SIZE];
	int			index;
	int			cread;
	struct s_fd	*next;
}				t_fd;

int				get_next_line(int fd, char **line);
void			buf_flush(t_fd *fdl);
int				buf_fill(t_fd *fdl);
void			copy_str(char **dst, char *src, size_t start, size_t len);
int				find_next_line(t_fd *fdl);
char			append(char **line, t_fd *fdl);

#endif
