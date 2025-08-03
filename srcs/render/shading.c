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
	diff = calc_diffuse(hit, data->light);
	col = vec_add(amb, diff);
	col = vec_clamp(col, 0.0f, 255.0f); 
	gamma = apply_gamma_correction(col);
	pixel = vector_to_int(gamma);
	return (pixel);
}
