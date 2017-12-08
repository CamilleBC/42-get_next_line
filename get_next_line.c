/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:34:58 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/08 17:40:25 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** If newline is null, it means it hasn't found a new line in the string.
** It means we have reach the end of line.
*/

static int	ft_copy_leftover(char **line, char fd_buffer[BUFF_SIZE], char *nl)
{
	if (nl == NULL)
		return (1);
	ft_strcpy(fd_buffer, &nl[1]);
	(*line)[nl - (*line)] = '\0';
	return (1);
}

/*
** 1- We keep reading unless we find a new line or we reach the end of file
** 2- We reallocate the old pointer with buffer size
** 3- As long as there are characters to read and we haven't encountered a
**	new line, we keep copying the data into line
**	We store the buffer in line, and then erase it
** 4- If we have already reached the end of file, we do not need to copy the
**	buffer. Otherwise we copy it to line.
*/

static int	read_line(const int fd, char fd_buffer[BUFF_SIZE], char **line)
{
	int32_t		status;
	char		*newline;
	uint32_t	len;

	while (((newline = ft_strchr(*line, '\n')) == NULL)
			&& ((status = read(fd, fd_buffer, BUFF_SIZE)) > FILE_READ))
	{
		len = ft_strlen(*line) + 1;
		if ((*line = ft_realloc(*line, len, len + BUFF_SIZE)) == NULL)
			return (ERROR);
		ft_strcat(*line, fd_buffer);
		ft_bzero(fd_buffer, BUFF_SIZE);
	}
	if ((**line != '\0') && (status >= FILE_READ))
		return (ft_copy_leftover(line, fd_buffer, newline));
	return (status);
}

/*
** 1- If the buffer is not empty, we allocate a new string and copy the buffer
**	contents
** 2- We loop in the buffer in case we have multiple new lines inside
*/

int			get_next_line(const int fd, char **line)
{
	static char	fd_array[ULIMIT_N][BUFF_SIZE + 1];
	int8_t		status;

	if (fd < 0 || fd > ULIMIT_N || line == NULL
			|| !(*line = ft_strnew(BUFF_SIZE + 1)))
		return (ERROR);
	if (fd_array[fd][0] != '\0')
		*line = ft_strcpy(*line, fd_array[fd]);
	ft_bzero(fd_array[fd], BUFF_SIZE + 1);
	status = read_line(fd, fd_array[fd], line);
	return (status);
}
