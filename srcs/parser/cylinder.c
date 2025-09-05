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

int	create_cylinder(t_data *data, t_cylinder *cylinder, t_color color)
{
	t_cylinder	*new_cylinder;
	t_shape		*shape;

	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_cylinder)
		return (0);
	new_cylinder->center = cylinder->center;
	new_cylinder->normal = cylinder->normal;
	new_cylinder->radius = cylinder->radius / 2.0f;
	new_cylinder->height = cylinder->height;
	shape = create_node(CYLINDER, new_cylinder, data);
	if (!shape)
	{
		free(new_cylinder);
		return (0);
	}
	shape->color = color;
	shape->material = build_material(color);
	append_node(data, shape);
	return (1);
}

void	parse_cylinder(char *line, t_data *data)
{
	char		**tokens;
	t_cylinder	cylinder;
	t_color		color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5])
		exit_free_all("Invalid cylinder line format", data, tokens);
	if (!validate_identifier(tokens[0], "cy"))
		exit_free_all("Invalid cylinder identifier", data, tokens);
	if (!validate_coordinates(tokens[1], &cylinder.center))
		exit_free_all("Invalid coordinates format for cylinder", data, tokens);
	if (!validate_coordinates(tokens[2], &cylinder.normal))
		exit_free_all("Invalid normalized vector", data, tokens);
	if (!validate_positive_float(tokens[3], &cylinder.radius))
		exit_free_all("Cylinder radius must be positive", data, tokens);
	if (!validate_positive_float(tokens[4], &cylinder.height))
		exit_free_all("Cylinder height must be positive", data, tokens);
	if (!validate_color(tokens[5], &color))
		exit_free_all("Invalid color format for cylinder", data, tokens);
	if (!create_cylinder(data, &cylinder, color))
		exit_free_all("Failed to create cylinder", data, tokens);
	free_array(tokens);
}
