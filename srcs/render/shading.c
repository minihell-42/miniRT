/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:11:42 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/08/03 18:29:13 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "render.h"

t_color	convert(t_vector *col)
{
	t_color	new;

	new.r = (int)fminf(fmaxf(col->x, 0.0f), 255.0f);
	new.g = (int)fminf(fmaxf(col->y, 0.0f), 255.0f);
	new.b = (int)fminf(fmaxf(col->z, 0.0f), 255.0f);
	return (new);
}

int	shade_pixel(t_inter *hit, t_data *data)
{
	t_vector	pos;
	t_vector	normal;
	t_vector	light_dir;
	t_vector	base;
	t_vector	amb;
	t_vector	col;
	t_color	end_col;
	float	diff;

	if (!inter_hit(hit))
		return (0x000000);
	pos = inter_pos(hit);
	normal = shape_normal(hit->shape, pos);
	light_dir = vec_normalize(vec_sub(data->light->coordinates, pos));
	diff = fmaxf(vec_dot(normal, light_dir), 0.0f);
	base.x = hit->color.r * data->light->ratio * diff;
	base.y = hit->color.g * data->light->ratio * diff;
	base.z = hit->color.b * data->light->ratio * diff;
	amb.x = (float)data->ambient->color.r;
	amb.y = (float)data->ambient->color.g;
	amb.z = (float)data->ambient->color.b;
	col = vec_clamp(vec_add(amb, base), 0.0f, 255.0f);
	col.x = powf(col.x / 255.0f, 1 / 2.2f) * 255.0f;
	col.y = powf(col.y / 255.0f, 1 / 2.2f) * 255.0f;
	col.z = powf(col.z / 255.0f, 1 / 2.2f) * 255.0f;
	end_col = convert(&col);
	return ((end_col.r << 16) | (end_col.g << 8) | end_col.b);
}
