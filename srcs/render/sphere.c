/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:44:27 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:44:29 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

// oc -> origin-to-center offset vector
// cand_dist -> candidate distance == not the final distance, needs validation
int	sphere_intersection(t_inter *hit, t_sphere *sp)
{
	t_vector	oc;
	t_quadratic	quad;
	float		cand_dist;

	oc = vec_sub(hit->ray.origin, sp->center);
	quad.a = vec_dot(hit->ray.direction, hit->ray.direction);
	quad.b = 2.0f * vec_dot(oc, hit->ray.direction);
	quad.c = vec_dot(oc, oc) - (sp->radius * sp->radius);
	if (!solve_quad(&quad))
		return (0);
	cand_dist = pick_quad_root(&quad, RAY_DIST_MIN, hit->dist);
	if (cand_dist < 0.0f)
		return (0);
	hit->dist = cand_dist;
	return (1);
}

t_vector	sphere_normal(t_sphere *sp, t_vector hit_point)
{
	return (vec_normalize(vec_sub(hit_point, sp->center)));
}
