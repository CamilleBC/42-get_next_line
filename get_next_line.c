/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:34:58 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/04 21:25:43 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	get_eol(int *eol, char *buffer)
{
	*eol = 0;
	while (*eol < BUFF_SIZE)
	{
		if (buffer[*eol] == '\n' || buffer[*eol] == '\0')
			return (SUCCESS);
		(*eol) += 1;
	}
	return (FAILURE);
}
static int	*read_buffer(const int fd, t_filedes *fd_array, char **line)
{
	int32_t		status;
	uint32_t	eol;
	uint32_t	len;
	char		buffer[BUFF_SIZE];
	char		*line_read;

	while ((status = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		if (*line_read != NULL)
			len = ft_strlen(line_read);
		else
			len = 1;
		// We reallocate the old pointer with buffer size
		if ((line_read = ft_realloc(line_read, len, len + BUFF_SIZE)) == NULL)
			return (NULL);
		// We find out if there is a new line somewhere. We use the index where
		// we found the newline, or EOL, and use str_sub to get the first part.
		// We store the first part in the buffer.
		if (get_eol(&eol, buffer) == SUCCESS)
		{
			ft_strlcat(line_read, buffer, eol);
			len = ft_strlen(line_read);
			ft_memcpy(buffer + eol, fd_array[fd].buffer, len - eol);
			break ;
		}
	}
	if (status == FILE_READ)
		return (FILE_READ);
	else if (status < 0)
		return (ERROR);
	return (LINE_READ);
}

/*
**
*/

int			get_next_line(const int fd, char **line)
{
	static t_filedes	fd_array[ULIMIT_N];
	char				*line_read;

	line_read = NULL;
	// If the buffer is not empty, we allocate a new string and copy the buffer
	// contents
	if (fd_array[fd].buffer != '\0')
	{
		if ((line_read = (char *)malloc(sizeof(char)
				* (ft_strlen(fd_array[fd].buffer) + 1))) == NULL)
			return (ERROR);
		ft_strcpy(*line_read, fd_array[fd].buffer);
		ft_memset(fd_array[fd].buffer, 0, BUFF_SIZE);
	}
	return (read_buffer(fd, &fd_array, &line_read));
}
