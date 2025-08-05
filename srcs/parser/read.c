/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:00:25 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:03:01 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	parse_line(char *line, t_data *data)
{
	clean_line(line);
	if (line[0] == 'A')
		parse_ambient(line, data);
	else if (line[0] == 'L')
		parse_light(line, data);
	else if (line[0] == 'C')
		parse_camera(line, data);
	else if (line[0] == 's' && line[1] == 'p')
		parse_sphere(line, data);
	else if (line[0] == 'p' && line[1] == 'l')
		parse_plane(line, data);
	else if (line[0] == 'c' && line[1] == 'y')
		parse_cylinder(line, data);
	else if (line[0] != '\0' && line[0] != '\t')
	{
		free(line);
		exit_free_data("Unknown identifier in file", data);
	}
}

static void	process_file(int fd, t_data *data)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, data);
		free(line);
		line = get_next_line(fd);
	}
}

void	read_file(char *file, t_data *data)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_free_data("Cannot open file", data);
	process_file(fd, data);
	close(fd);
}
