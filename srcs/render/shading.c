/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:11:42 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 19:09:24 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

int	vector_to_int(t_vector col)
{
	t_color	new;

	new.r = (int)fminf(fmaxf(col.x, 0.0f), 255.0f);
	new.g = (int)fminf(fmaxf(col.y, 0.0f), 255.0f);
	new.b = (int)fminf(fmaxf(col.z, 0.0f), 255.0f);
	return (new.r << 16 | new.g << 8 | new.b);
}

t_ray	make_shadow_ray(t_vector pos, t_vector normal, t_light *light)
{
	t_vector	to_light;
	t_vector	dir;
	t_vector	origin;
	float		dist;

	to_light = vec_sub(light->coordinates, pos);
	dist = vec_len(to_light);
	dir = vec_normalize(to_light);
	origin = vec_add(pos, vec_scalar_mult(normal, SHADOW_BIAS));
	return (ray_init(origin, dir, dist));
}

int	is_in_shadow(t_inter *hit, t_data *data)
{
	t_ray		shadow_ray;
	t_vector	pos;
	t_vector	normal;
	t_inter		blocker;

	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	shadow_ray = make_shadow_ray(pos, normal, data->light);
	blocker = cast_ray(&shadow_ray, data->shapes);
	if (blocker.shape && blocker.shape != hit->shape
		&& blocker.dist < shadow_ray.dist_max)
		return (1);
	return (0);
}

void	calc_specular(t_inter *hit, t_light *light, t_vector view_dir)
{
	t_vector	light_dir;
	t_vector	reflection_dir;
	t_vector	pos;
	float		reflection_dot_view;
	float		phong_factor;

	pos = inter_pos(hit);
	light_dir = vec_normalize(vec_sub(light->coordinates, pos));
	reflection_dir = vec_reflect(vec_negate(light_dir),
			shape_normal(hit->shape, pos));
	reflection_dot_view = fmaxf(vec_dot(reflection_dir, view_dir), 0.0f);
	phong_factor = powf(reflection_dot_view, hit->shape->material.shininess)
		* light->ratio;
	light->specular.x *= hit->shape->material.specular.x * phong_factor;
	light->specular.y *= hit->shape->material.specular.y * phong_factor;
	light->specular.z *= hit->shape->material.specular.z * phong_factor;
}

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector	final_color;
	t_vector	gamma_corrected;
	int			pixel_color;

	if (!inter_hit(hit))
		return (0x000000);
	final_color = calculate_lighting(hit, data);
	final_color = vec_clamp(final_color, 0.0f, 255.0f);
	gamma_corrected = apply_gamma_correction(final_color);
	pixel_color = vector_to_int(gamma_corrected);
	return (pixel_color);
}