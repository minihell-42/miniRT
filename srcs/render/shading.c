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
	origin = vec_add(pos, vec_scalar_mult(normal, RAY_DIST_MIN));
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
	return (inter_hit(&blocker));
}

// halfway vector
// specular = ks * spec_factor
t_vector	calc_specular(t_material mat, t_light *light, t_vector view_dir,
		t_vector hit_normal, t_vector hit_point)
{
	t_vector	L;
	t_vector	H;
	float		ndh;
	float		spec_factor;

	L = vec_normalize(vec_sub(light->coordinates, hit_point));
	H = vec_normalize(vec_add(L, view_dir));
	ndh = fmaxf(vec_dot(hit_normal, H), 0.0f);
	spec_factor = powf(ndh, mat.shininess) * light->ratio;
	return (vec_scalar_mult(mat.specular, spec_factor));
}

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector	diff;
	t_vector	col;
	t_vector	gamma;
	t_vector	amb;
	t_vector	spec;
	t_vector	view;
	t_vector	pos;
	t_vector	normal;
	t_material	mat;
	int			pixel;

	if (!inter_hit(hit))
		return (0x000000);
	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	mat = hit->shape->material;
	amb = convert_col_vec(data->ambient->color);
	amb = vec_scalar_mult(amb, data->ambient->ratio);
	view = vec_negate(hit->ray.direction);
	if (is_in_shadow(hit, data))
	{
		diff = (t_vector){0.0f, 0.0f, 0.0f};
		spec = (t_vector){0.0f, 0.0f, 0.0f};
	}
	else
	{
		diff = calc_diffuse(hit, data->light);
		spec = calc_specular(mat, data->light, view, normal, pos);
	}
	amb = vec_mult(amb, mat.diffuse);
	diff = vec_mult(diff, mat.diffuse);
	col = vec_add(vec_add(amb, diff), spec);
	col = vec_clamp(col, 0.0f, 255.0f);
	gamma = apply_gamma_correction(col);
	pixel = vector_to_int(gamma);
	return (pixel);
}
