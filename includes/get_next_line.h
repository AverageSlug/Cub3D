/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaurids <nlaurids@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 18:10:14 by nlaurids          #+#    #+#             */
/*   Updated: 2020/09/28 16:41:10 by nlaurids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

int		get_next_line(int fd, char **line);
int		ft_checkifendofline(char rest[BUFFER_SIZE + 1]);
int		ft_completeline(char **line, char rest[BUFFER_SIZE + 1]);
int		ft_reader(int fd, char buf[BUFFER_SIZE + 1],
		char rest[BUFFER_SIZE + 1]);
char	*ft_memcat(char *line, char rest[BUFFER_SIZE + 1]);

#endif
