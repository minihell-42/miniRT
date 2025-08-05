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

t_vector	convert_col_vec(t_color	color)
{
	t_vector	col_vec;

	col_vec.x = (float)color.r;
	col_vec.y = (float)color.g;
	col_vec.z = (float)color.b;
	return (col_vec);
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
