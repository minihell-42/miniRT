/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:00:23 by samcasti          #+#    #+#             */
/*   Updated: 2025/07/29 18:18:42 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_coordinates(char *str, t_vector *coords)
{
	char	**parts;
	int		success;

	if (!str || !coords)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_array(parts);
		return (0);
	}
	success = parse_float(parts[0], &coords->x)
		&& parse_float(parts[1], &coords->y)
		&& parse_float(parts[2], &coords->z);
	free_array(parts);
	return (success);
}

int	validate_color(char *str, t_color *color)
{
	char	**parts;
	int		success;

	if (!str || !color)
		return (0);
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_array(parts);
		return (0);
	}
	success = parse_int(parts[0], &color->r)
		&& parse_int(parts[1], &color->g)
		&& parse_int(parts[2], &color->b);
	if (success && (color->r < 0 || color->r > 255
			|| color->g < 0 || color->g > 255
			|| color->b < 0 || color->b > 255))
		success = 0;
	free_array(parts);
	return (success);
}

int	validate_ratio(char *str, float *ratio)
{
	if (!str || !ratio)
		return (0);
	*ratio = ft_atof(str);
	return (*ratio >= 0.0 && *ratio <= 1.0);
}

int	validate_fov(char *str, float *fov)
{
	if (!str || !fov)
		return (0);
	*fov = ft_atof(str);
	return (*fov > 0.0 && *fov <= 180.0);
}

int	validate_positive_float(char *str, float *value)
{
	if (!str || !value)
		return (0);
	*value = ft_atof(str);
	return (*value > 0.0);
}

int	validate_identifier(char *identifier, const char *expected)
{
	if (!identifier || !expected)
		return (0);
	return (ft_strcmp(identifier, (char *)expected) == 0);
}