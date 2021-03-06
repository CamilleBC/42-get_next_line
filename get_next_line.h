/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:34:50 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/08 17:57:50 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# include <stdio.h>

# define BUFF_SIZE	42
# define ULIMIT_N	(int32_t)4864
# define LINE_READ	(int8_t)1
# define FILE_READ	(int8_t)0
# define ERROR		(int8_t)-1
# define SUCCESS	(int8_t)0

typedef struct	s_filedes
{
	uint32_t	filedes;
	char		buffer[BUFF_SIZE];
}				t_filedes;

int				get_next_line(const int fd, char **line);

#endif
