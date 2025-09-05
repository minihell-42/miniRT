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

static int	create_plane(t_data *data, t_plane *plane, t_color color)
{
	t_plane	*new_plane;
	t_shape	*shape;

	new_plane = malloc(sizeof(t_plane));
	if (!new_plane)
		return (0);
	new_plane->point = plane->point;
	new_plane->normal = plane->normal;
	shape = create_node(PLANE, new_plane, data);
	if (!shape)
	{
		free(new_plane);
		return (0);
	}
	shape->color = color;
	shape->material = build_material(color);
	append_node(data, shape);
	return (1);
}

void	parse_plane(char *line, t_data *data)
{
	char	**tokens;
	t_plane	plane;
	t_color	color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid plane line format", data, tokens);
	if (!validate_identifier(tokens[0], "pl"))
		exit_free_all("Invalid plane identifier", data, tokens);
	if (!validate_coordinates(tokens[1], &plane.point))
		exit_free_all("Invalid coordinates for plane", data, tokens);
	if (!validate_coordinates(tokens[2], &plane.normal))
		exit_free_all("Invalid normalized vec for plane", data, tokens);
	if (!validate_color(tokens[3], &color))
		exit_free_all("Invalid color format for plane", data, tokens);
	if (!create_plane(data, &plane, color))
		exit_free_all("Failed to create plane", data, tokens);
	free_array(tokens);
}
