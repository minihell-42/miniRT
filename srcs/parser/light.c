/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:04:35 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:04:37 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_light(char *line, t_data *data)
{
	char		**tokens;
	float		ratio;
	t_vector	coordinates;

	if (data->light->is_set)
	{
		free(line);
		exit_free_data("Multiple light definitions found", data);
	}
	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2])
		exit_free_all("Invalid light line format", data, tokens);
	if (!validate_coordinates(tokens[1], &coordinates))
		exit_free_all("Invalid coordinates format for light", data, tokens);
	if (!validate_ratio(tokens[2], &ratio))
		exit_free_all("Light ratio must be between 0 and 1", data, tokens);
	data->light->coordinates = coordinates;
	data->light->ratio = ratio;
	data->light->is_set = 1;
	free_array(tokens);
}
