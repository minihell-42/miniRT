/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:16:31 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/10 15:17:23 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

// Helper to update hit->dist if intersection is valid and closer
void	update_closest_dist(float dist, t_inter *hit)
{
	if (dist > RAY_DIST_MIN && dist < hit->dist)
		hit->dist = dist;
}

// Computes the quadratic coefficients for the infinite cylinder side
int	cylinder_side_quadratic(t_ray *ray, t_cylinder *cy, t_quadratic *quad,
		t_vector *oc_perp)
{
	t_vector	oc;
	t_vector	dir_proj;
	float		dir_dot_n;
	float		oc_dot_n;

	oc = vec_sub(ray->origin, cy->center);
	dir_dot_n = vec_dot(ray->direction, cy->normal);
	dir_proj = vec_sub(ray->direction, vec_scalar_mult(cy->normal, dir_dot_n));
	quad->a = vec_dot(dir_proj, dir_proj);
	if (fabsf(quad->a) < RAY_DIST_MIN)
		return (0);
	oc_dot_n = vec_dot(oc, cy->normal);
	*oc_perp = vec_sub(oc, vec_scalar_mult(cy->normal, oc_dot_n));
	quad->b = 2.0f * vec_dot(dir_proj, *oc_perp);
	quad->c = vec_dot(*oc_perp, *oc_perp) - (cy->radius * cy->radius);
	return (1);
}
