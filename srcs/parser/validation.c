/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:00:23 by samcasti          #+#    #+#             */
/*   Updated: 2025/09/05 18:07:14 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
