/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:43:37 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:43:41 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

// intersect one disk cap at cap_center, return t or -1
// r2 -> radio al cuadrado
// denom -> denominador
static float	cap_intersect(t_ray *ray, t_cylinder *cy, t_vector cap_center)
{
	t_vector	point;
	float		denom;
	float		r2;
	float		dist;

	denom = vec_dot(ray->direction, cy->normal);
	if (fabsf(denom) < RAY_DIST_MIN)
		return (-1.0f);
	dist = vec_dot(vec_sub(cap_center, ray->origin), cy->normal) / denom;
	if (dist <= RAY_DIST_MIN)
		return (-1.0f);
	point = ray_at(ray, dist);
	r2 = cy->radius * cy->radius;
	if (vec_dot(vec_sub(point, cap_center), vec_sub(point, cap_center)) <= r2)
		return (dist);
	return (-1.0f);
}

// Checks if the intersection is within the finite cylinder height
static float	cylinder_side_intersection(t_ray *ray, t_cylinder *cy,
		float dist_max)
{
	t_quadratic	quad;
	t_vector	oc_perp;
	float		dist_side;
	float		half_height;
	float		height_proj;

	half_height = cy->height / 2.0f;
	if (!cylinder_side_quadratic(ray, cy, &quad, &oc_perp))
		return (-1.0f);
	if (!solve_quad(&quad))
		return (-1.0f);
	dist_side = pick_quad_root(&quad, RAY_DIST_MIN, dist_max);
	if (dist_side <= 0.0f)
		return (-1.0f);
	height_proj = vec_dot(vec_sub(ray_at(ray, dist_side), cy->center),
			cy->normal);
	if (fabsf(height_proj) > half_height + RAY_DIST_MIN)
		return (-1.0f);
	return (dist_side);
}

// Main intersection: checks side and caps, updates hit->dist if closer
int	cylinder_intersection(t_inter *hit, t_cylinder *cy)
{
	float		prev;
	t_vector	top_center;
	t_vector	bott_center;

	prev = hit->dist;
	update_closest_dist(cylinder_side_intersection(&hit->ray, cy, hit->dist),
		hit);
	bott_center = vec_sub(cy->center, vec_scalar_mult(cy->normal, cy->height
				/ 2.0f));
	top_center = vec_add(cy->center, vec_scalar_mult(cy->normal, cy->height
				/ 2.0f));
	update_closest_dist(cap_intersect(&hit->ray, cy, bott_center), hit);
	update_closest_dist(cap_intersect(&hit->ray, cy, top_center), hit);
	return (hit->dist < prev);
}

// oc -> origin-to-center
t_vector	cylinder_normal(t_cylinder *cy, t_vector hit_point)
{
	t_vector	oc;
	t_vector	proj;
	float		dist;
	float		half_height;

	half_height = cy->height / 2.0f;
	oc = vec_sub(hit_point, cy->center);
	dist = vec_dot(oc, cy->normal);
	if (dist <= -half_height + RAY_DIST_MIN)
		return (vec_negate(cy->normal));
	if (dist >= half_height - RAY_DIST_MIN)
		return (cy->normal);
	proj = vec_scalar_mult(cy->normal, dist);
	return (vec_normalize(vec_sub(oc, proj)));
}
