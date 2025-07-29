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

void	parse_cylinder(char *line, t_data *data)
{
	char		**tokens;
	t_vector	center;
	t_vector	normal;
	float		radius;
	float		height;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2]
		|| !tokens[3] || !tokens[4] || !tokens[5])
		exit_free_all("Invalid cylinder line format", data, tokens);
	if (!validate_coordinates(tokens[1], &center))
		exit_free_all("Invalid coordinates format for cylinder", data, tokens);
	if (!validate_coordinates(tokens[2], &normal))
		exit_free_all("Invalid normalized vector format for cylinder",
			data, tokens);
	if (!validate_positive_float(tokens[3], &radius))
		exit_free_all("Cylinder radius must be positive", data, tokens);
	if (!validate_positive_float(tokens[4], &height))
		exit_free_all("Cylinder height must be positive", data, tokens);
	data->cylinder->center = center;
	data->cylinder->normal = normal;
	data->cylinder->radius = radius;
	data->cylinder->height = height;
	free_array(tokens);
}
