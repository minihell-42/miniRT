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
	t_vector	L;
	t_vector	R;
	t_vector	pos;
	t_vector	normal;
	float		RdotV;
	float		phong_factor;

	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	L = vec_normalize(vec_sub(light->coordinates, pos));
	// perfect reflection of -L about N
	R = vec_reflect(vec_negate(L), normal);
	// cos angle between R and V
	RdotV = fmaxf(vec_dot(R, view_dir), 0.0f);
	// phong factor
	phong_factor = powf(RdotV, hit->shape->material.shininess) * light->ratio;
	light->specular.x *= hit->shape->material.specular.x * phong_factor;
	light->specular.y *= hit->shape->material.specular.y * phong_factor;
	light->specular.z *= hit->shape->material.specular.z * phong_factor;
}

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector diff;
	t_vector col;
	t_vector gamma;
	t_vector amb;
	t_vector view;
	int pixel;

	if (!inter_hit(hit))
		return (0x000000);
	amb = convert_col_vec(data->ambient->color);
	amb = vec_scalar_mult(amb, data->ambient->ratio);
	amb = vec_mult(amb, hit->shape->material.diffuse);
	view = vec_negate(hit->ray.direction);
	if (is_in_shadow(hit, data))
		diff = (t_vector){0.0f, 0.0f, 0.0f};
	else
	{
		diff = calc_diffuse(hit, data->light);
		calc_specular(hit, data->light, view);
	}
	diff = vec_mult(diff, hit->shape->material.diffuse);
	col = vec_add(vec_add(amb, diff), data->light->specular);
	col = vec_clamp(col, 0.0f, 255.0f);
	gamma = apply_gamma_correction(col);
	pixel = vector_to_int(gamma);
	return (pixel);
}