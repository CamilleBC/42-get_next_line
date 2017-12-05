/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 19:34:58 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/05 19:38:07 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(char fd_buffer[][BUFF_SIZE], char **line)
{
	char		*leftover;
	uint32_t	len;
	uint32_t	len_leftover;

	// ft_putstr("FD_BUFFER_RE2: '"); ft_putstr(*fd_buffer); ft_putstr("'\n");
	if ((leftover = ft_strchr(*fd_buffer, '\n')) != NULL)
	{
		len = ft_strlen(*fd_buffer);
		// ft_putstr("LEFTOVER: '"); ft_putstr(leftover); ft_putstr("'\n");
		len_leftover = ft_strlen(leftover);
		ft_strncpy(*line, *fd_buffer, (len - len_leftover));
		ft_memcpy(*fd_buffer, (leftover + 1), (len_leftover));
		ft_bzero(fd_buffer[len_leftover], (BUFF_SIZE - len_leftover - 1));
		// ft_putstr("FD_BUFFER_LEFT: '"); ft_putstr(*fd_buffer); ft_putstr("'\n");
		return (LINE_READ);
	}
	else
	{
		ft_strcpy(*line, *fd_buffer);
		ft_bzero(fd_buffer, BUFF_SIZE);
		return (SUCCESS);
	}

}

static int	read_line(const int fd, char fd_buffer[][BUFF_SIZE], char **line)
{
	int32_t		status;
	char		*leftover;
	uint32_t	len;
	uint32_t	len_leftover;
	char		buffer[BUFF_SIZE];

	while (1)
	{
		if (*line == NULL)
			len = 1;
		else
			len = ft_strlen(*line);
		// We reallocate the old pointer with buffer size
		if ((*line = ft_realloc(*line, len, len + BUFF_SIZE)) == NULL)
			return (ERROR);
		// We find out if there is a new line somewhere. We use the index where
		// we found the newline, or EOL, and use str_sub to get the first part.
		// We store the first part in the buffer.
		// ft_putstr("READ_LINE\n");
		if ((status = read(fd, buffer, BUFF_SIZE)) >= 0)
		{
			len = ft_strlen(buffer);
			// ft_putstr("BUFFER: '"); ft_putstr(buffer); ft_putstr("'\n");
			if ((leftover = ft_strchr(buffer, '\n')) != NULL)
			{
				len_leftover = ft_strlen(leftover);
				ft_strlcat(*line, buffer, (len - len_leftover + 1));
				ft_memcpy(*fd_buffer, (leftover + 1), (len_leftover));
				ft_bzero(fd_buffer[len_leftover], (BUFF_SIZE - len_leftover));
				// ft_putstr("FD_BUFFER: '"); ft_putstr(*fd_buffer); ft_putstr("'\n");
				break ;
			}
			else
				ft_strcat(*line, buffer);
			if (status == FILE_READ)
			{
				ft_bzero(*fd_buffer, BUFF_SIZE);
				return (FILE_READ);
			}
		}
	}
	if (status < 0)
		return (ERROR);
	return (LINE_READ);
}

int			get_next_line(const int fd, char **line)
{
	static t_filedes	fd_array[ULIMIT_N];
	// char				*line_read;
	int8_t				status;
	
	// If the buffer is not empty, we allocate a new string and copy the buffer
	// contents
	if (fd_array[fd].buffer[0] != '\0')
	{
		// ft_putstr("FD_BUFFER: '"); ft_putstr(fd_array[fd].buffer); ft_putstr("'\n");
		if ((*line = (char *)malloc(sizeof(char)
				* (ft_strlen(fd_array[fd].buffer) + 1))) == NULL)
			return (ERROR);
		if ((read_buffer(&(fd_array[fd].buffer), line)) == LINE_READ)
			return (LINE_READ);
	}
	// We loop in the buffer in case we have multiple new lines inside
	status = read_line(fd, &(fd_array[fd].buffer), line);
	// ft_putstr("GNL status: "); ft_putnbr(status);
	return(status);
}
