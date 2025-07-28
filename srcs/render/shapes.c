/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:44:07 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:44:09 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// did_hit -> boolean to know if there is an intersection
int	shape_intersect(t_inter *hit, const t_shape *shape)
{
	int	did_hit;

	did_hit = 0;
	if (shape->shape_type == SPHERE)
		did_hit = sphere_intersection(hit, (t_sphere *)shape->object);
	else if (shape->shape_type == PLANE)
		did_hit = plane_intersection(hit, (t_plane *)shape->object);
	else
		did_hit = cylinder_intersection(hit, (t_cylinder *)shape->object);
	if (did_hit)
	{
		hit->shape = (t_shape *)shape;
		hit->color = shape->color;
	}
	return (did_hit);
}

t_vector	shape_normal(const t_shape *shape, t_vector hit_point)
{
	if (shape->shape_type == SPHERE)
		return (sphere_normal((t_sphere *)shape->object, hit_point));
	else if (shape->shape_type == PLANE)
		return (plane_normal((t_plane *)shape->object, hit_point));
	else
		return (cylinder_normal((t_cylinder *)shape->object, hit_point));
}

void	ft_swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	solve_quad(t_quadratic *quad)
{
	float	disc;

	disc = quad->b * quad->b - 4.0f * quad->a * quad->c;
	if (disc < 0.0f)
	{
		quad->sol_count = 0;
		return (0);
	}
	else if (disc == 0.0f)
	{
		quad->dist0 = -quad->b / (2.0f * quad->a);
		quad->dist1 = quad->dist0;
		quad->sol_count = 1;
	}
	else
	{
		quad->square = sqrtf(disc);
		quad->dist0 = (-quad->b - quad->square) / (2.0f * quad->a);
		quad->dist1 = (-quad->b + quad->square) / (2.0f * quad->a);
		if (quad->dist0 > quad->dist1)
			ft_swap(&quad->dist0, &quad->dist1);
		quad->sol_count = 2;
	}
	return (quad->sol_count);
}

float	pick_quad_root(const t_quadratic *quad, float dist_min, float dist_max)
{
	if (quad->sol_count == 0)
		return (-1.0f);
	else if (quad->sol_count == 1)
	{
		if (quad->dist0 > dist_min && quad->dist0 < dist_max)
			return (quad->dist0);
		else
			return (-1.0f);
	}
	if (quad->dist0 > dist_min && quad->dist0 < dist_max)
		return (quad->dist0);
	if (quad->dist1 > dist_min && quad->dist1 < dist_max)
		return (quad->dist1);
	return (-1.0f);
}
