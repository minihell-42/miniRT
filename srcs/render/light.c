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

t_vector	convert_col_vec(t_color color)
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
	t_vector	obj_col;
	t_vector	kd;
	float		NdotL;

	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	light_dir = vec_normalize(vec_sub(light->coordinates, pos));
	NdotL = fmaxf(vec_dot(normal, light_dir), 0.0f);
	// object base color as float
	obj_col = convert_col_vec(hit->shape->color);
	// material diffuse rgb (each in [0..1])
	kd = hit->shape->material.diffuse;
	// final diffuse per channel
	return ((t_vector){obj_col.x * kd.x * light->ratio * NdotL, obj_col.y * kd.y
		* light->ratio * NdotL, obj_col.z * kd.z * light->ratio * NdotL});
}
