/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:04:00 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:05:44 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_plane(t_data *data, t_vector point, t_vector normal, t_color color)
{
	t_plane	*plane;
	t_shape	*shape;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	plane->point = point;
	plane->normal = normal;
	shape = create_node(PLANE, plane, data);
	if (!shape)
	{
		free(plane);
		return (0);
	}
	shape->color = color;
	append_node(data, shape);
	return (1);
}

void	parse_plane(char *line, t_data *data)
{
	char		**tokens;
	t_vector	point;
	t_vector	normal;
	t_color		color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid plane line format", data, tokens);
	if (!validate_coordinates(tokens[1], &point))
		exit_free_all("Invalid coordinates for plane", data, tokens);
	if (!validate_coordinates(tokens[2], &normal))
		exit_free_all("Invalid normalized vec for plane", data, tokens);
	if (!validate_color(tokens[3], &color))
		exit_free_all("Invalid color format for plane", data, tokens);
	if (!create_plane(data, point, normal, color))
		exit_free_all("Failed to create plane", data, tokens);
	free_array(tokens);
}
