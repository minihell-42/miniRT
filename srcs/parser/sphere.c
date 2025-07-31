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

int	create_sphere(t_data *data, t_vector center, float radius, t_color color)
{
	t_sphere	*sphere;
	t_shape		*shape;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->center = center;
	sphere->radius = radius;
	shape = create_node(SPHERE, sphere, data);
	if (!shape)
	{
		free(sphere);
		return (0);
	}
	shape->color = color;
	append_node(data, shape);
	return (1);
}

void	parse_sphere(char *line, t_data *data)
{
	char		**tokens;
	t_vector	center;
	float		radius;
	t_color		color;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid sphere line format", data, tokens);
	if (!validate_coordinates(tokens[1], &center))
		exit_free_all("Invalid coordinates format for sphere", data, tokens);
	if (!validate_positive_float(tokens[2], &radius))
		exit_free_all("Sphere radius must be positive", data, tokens);
	if (!validate_color(tokens[3], &color))
		exit_free_all("Invalid color format for sphere", data, tokens);
	if (!create_sphere(data, center, radius, color))
		exit_free_all("Failed to create sphere", data, tokens);
	free_array(tokens);
}
