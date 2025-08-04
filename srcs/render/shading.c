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

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector	diff;
	t_vector	col;
	t_vector	gamma;
	t_vector	amb;
	int			pixel;

	if (!inter_hit(hit))
		return (0x000000);
	amb = convert_amb_vec(data->ambient);
	if (is_in_shadow(hit, data))
		diff = (t_vector){0.0f, 0.0f, 0.0f};
	else
		diff = calc_diffuse(hit, data->light);
	col = vec_add(amb, diff);
	col = vec_clamp(col, 0.0f, 255.0f);
	gamma = apply_gamma_correction(col);
	pixel = vector_to_int(gamma);
	return (pixel);
}
