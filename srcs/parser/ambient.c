/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:10:33 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:10:35 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	parse_ambient(char *line, t_data *data)
{
	char	**tokens;
	float	ratio;
	t_color	color;

	if (data->ambient->is_set)
		exit_free_data("Multiple ambient light definitions found", data);
	tokens = ft_split(line, '\t');
	if (!tokens)
		exit_free_data("Memory allocation failed", data);
	if (!tokens[0] || !tokens[1] || !tokens[2])
		exit_free_all("Invalid ambient format", data, tokens);
	if (!validate_ratio(tokens[1], &ratio))
		exit_free_all("Ambient ratio must be between 0 and 1", data, tokens);
	if (!validate_color(tokens[2], &color))
		exit_free_all("Invalid color format for ambient", data, tokens);
	data->ambient->ratio = ratio;
	data->ambient->color = color;
	data->ambient->is_set = 1;
	free_array(tokens);
}
