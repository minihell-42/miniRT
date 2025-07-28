/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:43:54 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:43:55 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// denorm -> denominador
int	plane_intersection(t_inter *hit, const t_plane *pl)
{
	float		denom;
	float		dist_val;
	t_vector	diff;

	denom = vec_dot(hit->ray.direction, pl->normal);
	if (fabsf(denom) < EPSILON)
		return (0);
	diff = vec_sub(pl->point, hit->ray.origin);
	dist_val = vec_dot(diff, pl->normal) / denom;
	if (dist_val <= RAY_DIST_MIN || dist_val >= hit->dist)
		return (0);
	hit->dist = dist_val;
	return (1);
}

t_vector	plane_normal(const t_plane *pl, t_vector hit_point)
{
	(void)hit_point;
	return (pl->normal);
}
