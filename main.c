/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamashis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 08:19:52 by kamashis          #+#    #+#             */
/*   Updated: 2017/08/24 12:22:41 by kamashis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int     main(int ac, char **av)
{
	int fd;
	char    *line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &line))
		{
			printf("%s\n", line);
			free(line);
		}
	}
	return (0);
}
