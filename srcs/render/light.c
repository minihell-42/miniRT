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

t_vector	calculate_lighting(t_inter *hit, t_data *data)
{
	t_vector	diffuse_light;
	t_vector	ambient_light;
	t_vector	view_dir;
	t_vector	total_light;

	ambient_light = convert_col_vec(data->ambient->color);
	ambient_light = vec_scalar_mult(ambient_light, data->ambient->ratio);
	ambient_light = vec_mult(ambient_light, hit->shape->material.diffuse);
	view_dir = vec_negate(hit->ray.direction);
	if (is_in_shadow(hit, data))
		diffuse_light = (t_vector){0.0f, 0.0f, 0.0f};
	else
	{
		diffuse_light = calc_diffuse(hit, data->light);
		calc_specular(hit, data->light, view_dir);
	}
	diffuse_light = vec_mult(diffuse_light, hit->shape->material.diffuse);
	total_light = vec_add(vec_add(ambient_light, diffuse_light),
			data->light->specular);
	return (total_light);
}