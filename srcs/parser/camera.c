/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:09:41 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:10:15 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_camera(char *line, t_data *data)
{
	char		**tokens;
	t_vector	coordinates;
	t_vector	normalized;
	float		fov;

	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3])
		exit_free_all("Invalid camera format", data, tokens);
	if (!validate_coordinates(tokens[1], &coordinates))
		exit_free_all("Invalid coordinates format for camera", data, tokens);
	if (!validate_coordinates(tokens[2], &normalized))
		exit_free_all("Invalid normalized vec for camera", data, tokens);
	if (!validate_fov(tokens[3], &fov))
		exit_free_all("Camera FOV must be between 0 and 180", data, tokens);
	data->camera->coordinates = coordinates;
	data->camera->normalized = normalized;
	data->camera->fov = fov;
	free_array(tokens);
}
