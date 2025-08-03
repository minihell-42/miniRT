/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:43:46 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/07/28 11:43:48 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"
#include "render.h"

t_inter	inter_init(t_ray *ray)
{
	t_inter	inter;

	inter.ray = *ray;
	inter.dist = ray->dist_max;
	inter.shape = NULL;
	return (inter);
}

t_vector	inter_pos(t_inter *inter)
{
	return (ray_at(&inter->ray, inter->dist));
}

int	inter_hit(t_inter *inter)
{
	return (inter->shape != NULL);
}

t_inter	cast_ray(t_ray *ray, t_shape *shapes)
{
	t_inter	hit;
	t_shape	*curr_shape;

	hit = inter_init(ray);
	curr_shape = shapes;
	while (curr_shape)
	{
		shape_intersect(&hit, curr_shape);
		curr_shape = curr_shape->next;
	}
	return (hit);
}
