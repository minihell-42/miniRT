/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:01:07 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 19:09:48 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	create_sphere(t_data *data, t_sphere *sphere, t_color color)
{
	t_sphere	*new_sphere;
	t_shape		*shape;

	new_sphere = malloc(sizeof(t_sphere));
	if (!new_sphere)
		return (0);
	new_sphere->center = sphere->center;
	new_sphere->radius = sphere->radius / 2.0f;
	shape = create_node(SPHERE, new_sphere, data);
	if (!shape)
	{
		free(new_sphere);
		return (0);
	}
	shape->color = color;
	shape->material = build_material(color);
	append_node(data, shape);
	return (1);
}

void	parse_sphere(char *line, t_data *data)
{
	char		**tokens;
	t_sphere	sphere;
	t_color		color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid sphere line format", data, tokens);
	if (!validate_coordinates(tokens[1], &sphere.center))
		exit_free_all("Invalid coordinates format for sphere", data, tokens);
	if (!validate_positive_float(tokens[2], &sphere.radius))
		exit_free_all("Sphere radius must be positive", data, tokens);
	if (!validate_color(tokens[3], &color))
		exit_free_all("Invalid color format for sphere", data, tokens);
	if (!create_sphere(data, &sphere, color))
		exit_free_all("Failed to create sphere", data, tokens);
	free_array(tokens);
}
