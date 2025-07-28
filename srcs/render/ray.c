/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:44:00 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:44:02 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_ray	ray_init(t_vector origin, t_vector direction, float dist_max)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec_normalize(direction);
	ray.dist_max = dist_max;
	return (ray);
}

t_ray	ray_init_default(t_vector origin, t_vector direction)
{
	return (ray_init(origin, direction, RAY_DIST_MAX));
}

t_vector	ray_at(const t_ray *ray, float dist)
{
	return (vec_add(ray->origin, vec_scalar_mult(ray->direction, dist)));
}
