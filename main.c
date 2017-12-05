/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaillat <cbaillat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 08:50:34 by cbaillat          #+#    #+#             */
/*   Updated: 2017/12/05 09:40:38 by cbaillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int32_t	fd;
	char	**line_read;

	if (ac <= 1)
		return (0);
	while (--ac > 1)
	{
		fd = open(av[ac], O_RDONLY);
	}
	while (get_next_line(fd, line_read) >= FILE_READ)
		ft_putstr()
}
