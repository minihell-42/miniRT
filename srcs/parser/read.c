/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:00:25 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/25 14:10:36 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*read_file(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		system_error("Cannot open file");
	while ((line = get_next_line(fd)) != NULL)
	{
		
        if (line[0] == 'A')
            parse_ambient(line);
        else if(line[0] == 'L')
            parse_light(line);
        else if(line[0] == 'C')
            parse_camera(line);
		// ft_printf("%c\n", line[0]);
		free(line);
	}
	close(fd);
	return (0);
}
