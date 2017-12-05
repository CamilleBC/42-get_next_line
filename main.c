/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 08:50:34 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/05 19:45:38 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int32_t	i;
	int32_t	*fd;
	int32_t	status;
	char	*line_read;

	if (ac <= 1)
		return (0);
	if ((fd = malloc(sizeof(*fd) * (ac - 1))) == NULL)
		return (ERROR);
	fd[0] = open(av[1], O_RDONLY);
	i = 0;
	line_read = NULL;
	while (1)
	{
		status = get_next_line(fd[i], &line_read);
		// printf("status: %d\n", status);
		if (status == ERROR)
			return (ERROR);
		if (status == FILE_READ)
			return (SUCCESS);
		ft_putstr(line_read);
	}
	return (SUCCESS);
}
