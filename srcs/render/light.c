/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:11:19 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/10 10:39:33 by dgomez-a         ###   ########.fr       */
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
	t_vector	light_direction;
	t_vector	object_color;
	t_vector	material_diffuse;
	t_vector	diffuse_result;
	float		normal_dot_light;

	light_direction = vec_normalize(vec_sub(light->coordinates, hit->pos));
	normal_dot_light = fmaxf(vec_dot(hit->normal, light_direction), 0.0f);
	object_color = convert_col_vec(hit->shape->color);
	material_diffuse = hit->shape->material.diffuse;
	diffuse_result.x = object_color.x * material_diffuse.x * light->ratio
		* normal_dot_light;
	diffuse_result.y = object_color.y * material_diffuse.y * light->ratio
		* normal_dot_light;
	diffuse_result.z = object_color.z * material_diffuse.z * light->ratio
		* normal_dot_light;
	return (diffuse_result);
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
