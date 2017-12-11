/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 08:50:34 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/11 10:36:20 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int32_t	i;
	int32_t	fd;
	int32_t	status;
	char	*line_read;

	if (ac <= 1)
		return (0);
	fd = open(av[1], O_RDONLY);
	i = 0;
	line_read = NULL;
	while (1)
	{
		status = get_next_line(fd, &line_read);
		// printf("status: %d\n", status);
		if (status == ERROR)
		{
			free (line_read);
			return (ERROR);
		}
		if (status == FILE_READ)
		{
			free (line_read);
			return (SUCCESS);
		}
		ft_putstr(line_read);
		free (line_read);
	}
	return (SUCCESS);
}
