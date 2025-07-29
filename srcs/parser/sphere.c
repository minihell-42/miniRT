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
		exit_free_all("Sphere radius must be positive", data, tokens);
	free_array(tokens);
}
