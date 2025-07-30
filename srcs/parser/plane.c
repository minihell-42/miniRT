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

void	parse_plane(char *line, t_data *data)
{
	char		**tokens;
	t_vector	point;
	t_vector	normal;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid plane line format", data, tokens);
	if (!validate_coordinates(tokens[1], &point))
		exit_free_all("Invalid coordinates for plane", data, tokens);
	if (!validate_coordinates(tokens[2], &normal))
		exit_free_all("Invalid normalized vec for plane", data, tokens);
	data->plane->point = point;
	data->plane->normal = normal;
	free_array(tokens);
}
