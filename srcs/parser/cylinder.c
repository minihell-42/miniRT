/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:07:21 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:08:18 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	create_cylinder(t_data *data, t_vector center, t_vector normal,
		float radius, float height, t_color color)
{
	t_cylinder	*cylinder;
	t_shape		*shape;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->center = center;
	cylinder->normal = normal;
	cylinder->radius = radius;
	cylinder->height = height;
	shape = create_node(CYLINDER, cylinder, data);
	if (!shape)
	{
		free(cylinder);
		return (0);
	}
	shape->color = color;
	append_node(data, shape);
	return (1);
}

void	parse_cylinder(char *line, t_data *data)
{
	char		**tokens;
	t_vector	center;
	t_vector	normal;
	float		radius;
	float		height;
	t_color		color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5])
		exit_free_all("Invalid cylinder line format", data, tokens);
	if (!validate_coordinates(tokens[1], &center))
		exit_free_all("Invalid coordinates format for cylinder", data, tokens);
	if (!validate_coordinates(tokens[2], &normal))
		exit_free_all("Invalid normalized vector", data, tokens);
	if (!validate_positive_float(tokens[3], &radius))
		exit_free_all("Cylinder radius must be positive", data, tokens);
	if (!validate_positive_float(tokens[4], &height))
		exit_free_all("Cylinder height must be positive", data, tokens);
	if (!validate_color(tokens[5], &color))
		exit_free_all("Invalid color format for cylinder", data, tokens);
	if (!create_cylinder(data, center, normal, radius, height, color))
		exit_free_all("Failed to create cylinder", data, tokens);
	free_array(tokens);
}
