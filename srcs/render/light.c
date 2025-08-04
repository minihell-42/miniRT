/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:11:19 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:49:20 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

void	ambient_computation(t_ambient *amb)
{
	amb->color.r *= amb->ratio;
	amb->color.g *= amb->ratio;
	amb->color.b *= amb->ratio;
}

t_vector	convert_amb_vec(t_ambient *amb)
{
	t_vector	amb_vec;

	amb_vec.x = (float)amb->color.r;
	amb_vec.y = (float)amb->color.g;
	amb_vec.z = (float)amb->color.b;
	return (amb_vec);
}

t_vector	calc_diffuse(t_inter *hit, t_light *light)
{
	t_vector	pos;
	t_vector	normal;
	t_vector	light_dir;
	t_vector	base;
	float		diff;

	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	light_dir = vec_normalize(vec_sub(light->coordinates, pos));
	diff = vec_dot(normal, light_dir);
	if (diff < 0.0f)
		diff = 0.0f;
	base.x = hit->color.r * light->ratio * diff;
	base.y = hit->color.g * light->ratio * diff;
	base.z = hit->color.b * light->ratio * diff;
	return (base);
}
